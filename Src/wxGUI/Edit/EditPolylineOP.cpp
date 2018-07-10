#ifndef _WX_GUI_EDIT_POLYLINE_OP_CPP_
#define _WX_GUI_EDIT_POLYLINE_OP_CPP_

#include "EditPolylineOP.h"

#include "Render/PrimitiveDraw.h"

//using namespace wxgui;

template <typename TBase, typename TSelected, typename TCMPT>
wxgui::EditPolylineOP<TBase, TSelected, TCMPT>::
EditPolylineOP(EditPanel* editPanel, MultiShapesImpl* shapesImpl, TCMPT* cmpt)
	: TBase(editPanel, shapesImpl)
{
	m_shapesImpl = shapesImpl;

	m_cmpt = cmpt;

	m_selectOP = new TSelected(editPanel, shapesImpl, cmpt);
	m_lastLeftDownPos.setInvalid();
	m_bSelectOpen = false;
}

template <typename TBase, typename TSelected, typename TCMPT>
wxgui::EditPolylineOP<TBase, TSelected, TCMPT>::
~EditPolylineOP() 
{
	delete m_selectOP;
}

template <typename TBase, typename TSelected, typename TCMPT>
bool wxgui::EditPolylineOP<TBase, TSelected, TCMPT>::
onKeyDown(int keyCode) 
{
	return m_selectOP->onKeyDown(keyCode);
}

template <typename TBase, typename TSelected, typename TCMPT>
bool wxgui::EditPolylineOP<TBase, TSelected, TCMPT>::
onMouseLeftDown(int x, int y) 
{
	bool bNotDeliver = false;

	if (shouldFixMousePos())
		bNotDeliver = TBase::onMouseLeftDown(x, y);
	else
	{
		int tolerance;
		if (m_cmpt)
			tolerance = m_cmpt->getNodeCaptureDistance();
		else
			tolerance = 0;
		if (tolerance != 0)
		{	
			NodeCapture capture(m_shapesImpl, tolerance);
			f2Vec2 pos = m_editPanel->transPosScreenToProject(x, y);
			capture.captureEditable(pos, m_capturedEditable);
			if (!m_capturedEditable.chain)
				capture.captureSelectable(pos, m_captureSelectable);
		}

		if (m_capturedEditable.chain)
		{
// 			f2Vec2 screen = m_editPanel->transPosProjectToScreen(m_capturedEditable.pos);
// 			bNotDeliver = TBase::onMouseLeftDown(screen.x, screen.y);

			m_polyline.push_back(m_capturedEditable.pos);
		}
		else if (m_captureSelectable.chain)
		{
			m_polyline.push_back(m_captureSelectable.pos);
		}
		else
		{
			if (m_polyline.empty())
				m_lastLeftDownPos = f2Vec2(x, y);

			if (tolerance != 0 && m_polyline.empty())
			{
				f2Vec2 pos = m_editPanel->transPosScreenToProject(x, y);
				InterruptChainVisitor interrupt(pos, tolerance);
				m_shapesImpl->traverseShapes(interrupt, e_editable);
				if (interrupt.getInterruptedChain())
				{
					m_capturedEditable.chain = interrupt.getInterruptedChain();
					m_capturedEditable.pos = pos;
					m_editPanel->Refresh();
				}
				else
					bNotDeliver = TBase::onMouseLeftDown(x, y);
			}
			else
				bNotDeliver = TBase::onMouseLeftDown(x, y);
		}
	}

	return bNotDeliver;
}

template <typename TBase, typename TSelected, typename TCMPT>
bool wxgui::EditPolylineOP<TBase, TSelected, TCMPT>::
onMouseLeftUp(int x, int y) 
{
	if (TBase::onMouseLeftUp(x, y)) return true;

	if (m_bSelectOpen)
	{
		m_selectOP->onMouseLeftUp(x, y);
		m_bSelectOpen = false;
		m_lastLeftDownPos.setInvalid();
	}

	return false;
}

template <typename TBase, typename TSelected, typename TCMPT>
bool wxgui::EditPolylineOP<TBase, TSelected, TCMPT>::
onMouseRightDown(int x, int y) 
{
	if (m_polyline.empty())
	{
		int tolerance;
		if (m_cmpt)
			tolerance = m_cmpt->getNodeCaptureDistance();
		else
			tolerance = 0;
		if (tolerance != 0)
		{
			NodeCapture capture(m_shapesImpl, tolerance);
			capture.captureEditable(m_editPanel->transPosScreenToProject(x, y), m_capturedEditable);
			if (m_capturedEditable.chain)
			{
				m_capturedEditable.chain->removeVertices(m_capturedEditable.pos);
				m_capturedEditable.chain = NULL;
				m_editPanel->Refresh();
			}
		}

		return false;
	}
	else
	{
		return TBase::onMouseRightDown(x, y);
	}
}

template <typename TBase, typename TSelected, typename TCMPT>
bool wxgui::EditPolylineOP<TBase, TSelected, TCMPT>::
onMouseMove(int x, int y) 
{
	if (TBase::onMouseMove(x, y)) return true;

	int tolerance;
	if (m_cmpt)
		tolerance = m_cmpt->getNodeCaptureDistance();
	else
		tolerance = 0;
	if (tolerance != 0)
	{
		f2Vec2 pos = m_editPanel->transPosScreenToProject(x, y);
		NodeCapture capture(m_shapesImpl, tolerance);
		{
			ChainShape* oldChain = m_capturedEditable.chain;
			capture.captureEditable(pos, m_capturedEditable);
			if (oldChain && !m_capturedEditable.chain || !oldChain && m_capturedEditable.chain)
				m_editPanel->Refresh();
		}
		{
			ChainShape* oldChain = m_captureSelectable.chain;
			capture.captureSelectable(pos, m_captureSelectable);
			if (oldChain && !m_captureSelectable.chain || !oldChain && m_captureSelectable.chain)
				m_editPanel->Refresh();
		}
	}

	return false;
}

template <typename TBase, typename TSelected, typename TCMPT>
bool wxgui::EditPolylineOP<TBase, TSelected, TCMPT>::
onMouseDrag(int x, int y) 
{
	if (TBase::onMouseDrag(x, y)) return true;

	if (m_bSelectOpen)
		m_selectOP->onMouseDrag(x, y);
	else if (m_capturedEditable.chain)
	{
		if (m_polyline.size() > 1)
		{
			m_capturedEditable.chain = NULL;
			return false;
		}

		if (m_polyline.size() == 1)
			m_polyline.clear();

		f2Vec2 pos = m_editPanel->transPosScreenToProject(x, y);
		m_capturedEditable.chain->changeVertices(m_capturedEditable.pos, pos);
		m_capturedEditable.chain->refresh();
		m_capturedEditable.pos = pos;
		m_editPanel->Refresh();
	}
	else if (m_lastLeftDownPos.isValid() 
		&& f2Math::getDistance(m_lastLeftDownPos, f2Vec2(x, y)) < DRAG_SELECT_TOL)
		//		&& (m_lastLeftDownPos.x != x || m_lastLeftDownPos.y != y))
	{
		if (m_polyline.size() == 1)
			m_polyline.clear();
		m_bSelectOpen = true;
		m_selectOP->onMouseLeftDown(x, y);
	}

	return false;
}

template <typename TBase, typename TSelected, typename TCMPT>
bool wxgui::EditPolylineOP<TBase, TSelected, TCMPT>::
onDraw() const 
{
	if (TBase::onDraw()) return true;

	m_selectOP->onDraw();
	if (m_cmpt)
	{
		if (m_capturedEditable.chain)
			PrimitiveDraw::drawCircle(m_capturedEditable.pos, m_cmpt->getNodeCaptureDistance(), f2Colorf(1.0f, 0.4f, 0.4f));
		else if (m_captureSelectable.chain)
			PrimitiveDraw::drawCircle(m_captureSelectable.pos, m_cmpt->getNodeCaptureDistance(), f2Colorf(1.0f, 0.4f, 0.4f));
	}

	return false;
}

template <typename TBase, typename TSelected, typename TCMPT>
bool wxgui::EditPolylineOP<TBase, TSelected, TCMPT>::
clear() 
{
	if (TBase::clear()) return true;

	m_selectOP->clear();
	m_capturedEditable.chain = NULL;
	m_captureSelectable.chain = NULL;

	return false;
}

//////////////////////////////////////////////////////////////////////////
// class EditPolylineOP::NodeCapture
//////////////////////////////////////////////////////////////////////////

template <typename TBase, typename TSelected, typename TCMPT>
wxgui::EditPolylineOP<TBase, TSelected, TCMPT>::NodeCapture::
NodeCapture(MultiShapesImpl* shapesImpl, int tol)
	: m_shapesImpl(shapesImpl)
	, m_tol(tol)
{
}

template <typename TBase, typename TSelected, typename TCMPT>
void wxgui::EditPolylineOP<TBase, TSelected, TCMPT>::NodeCapture::
captureEditable(const f2Vec2& pos, NodeAddr& result) 
{
	m_shapesImpl->traverseShapes(QueryChainVisitor(pos, m_tol, result), e_editable);
}

template <typename TBase, typename TSelected, typename TCMPT>
void wxgui::EditPolylineOP<TBase, TSelected, TCMPT>::NodeCapture::
captureSelectable(const f2Vec2& pos, NodeAddr& result) 
{
	m_shapesImpl->traverseShapes(QueryChainVisitor(pos, m_tol, result), e_selectable);
}

template <typename TBase, typename TSelected, typename TCMPT>
wxgui::EditPolylineOP<TBase, TSelected, TCMPT>::NodeCapture::QueryChainVisitor::
QueryChainVisitor(const f2Vec2& pos, float tolerance, NodeAddr& result)
	: m_pos(pos)
	, m_tolerance(tolerance)
	, m_aabb(pos, tolerance, tolerance)
	, m_result(result)
{
	result.chain = NULL;
}

template <typename TBase, typename TSelected, typename TCMPT>
void wxgui::EditPolylineOP<TBase, TSelected, TCMPT>::NodeCapture::QueryChainVisitor::
visit(IObject* object, bool& bFetchNext) 
{
	ChainShape* chain = static_cast<ChainShape*>(object);

	if (!f2Math::isAABBIntersectAABB(m_aabb, chain->getAABB()))
	{
		bFetchNext = true;
		return;
	}

	if (!chain->isIntersect(m_aabb)) 
	{
		bFetchNext = true;
		return;
	}

	const std::vector<f2Vec2>& vertices = chain->getVertices();
	for (size_t i = 0, n = vertices.size(); i < n; ++i)
	{
		if (f2Math::getDistance(vertices[i], m_pos) < m_tolerance)
		{
			m_result.chain = chain;
			m_result.pos = vertices[i];
			bFetchNext = false;
			return;
		}
	}

	bFetchNext = true;
}

//////////////////////////////////////////////////////////////////////////
// class EditPolylineOP::InterruptChainVisitor
//////////////////////////////////////////////////////////////////////////

template <typename TBase, typename TSelected, typename TCMPT>
wxgui::EditPolylineOP<TBase, TSelected, TCMPT>::InterruptChainVisitor::
InterruptChainVisitor(const f2Vec2& pos, int tol)
	: m_pos(pos)
	, m_tol(tol)
	, m_chain(NULL)
{
}

template <typename TBase, typename TSelected, typename TCMPT>
void wxgui::EditPolylineOP<TBase, TSelected, TCMPT>::InterruptChainVisitor::
visit(IObject* object, bool& bFetchNext) 
{
	f2AABB query(m_pos, m_tol, m_tol);

	ChainShape* chain = static_cast<ChainShape*>(object);
	if (!chain->isIntersect(query)) 
	{
		bFetchNext = true;
		return;
	}

	size_t iPos;
	const std::vector<f2Vec2>& vertices = chain->getVertices();
	float dis = f2Math::getDisPointToPolyline(m_pos, vertices, &iPos);
	if (dis < m_tol)
	{
		chain->insertVertices(iPos + 1, m_pos);
		m_chain = chain;
		bFetchNext = false;
		return;
	}
	else if (chain->isClosed() && vertices.size() > 1)
	{
		float dis = f2Math::getDisPointToSegment(m_pos, vertices.front(), vertices.back());
		if (dis < m_tol)
		{
			chain->insertVertices(vertices.size(), m_pos);
			m_chain = chain;
			bFetchNext = false;
			return;
		}
	}

	bFetchNext = true;
}

#endif // _WX_GUI_EDIT_POLYLINE_OP_CPP_