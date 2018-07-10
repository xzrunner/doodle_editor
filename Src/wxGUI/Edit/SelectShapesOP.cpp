#include "SelectShapesOP.h"

#include "Dataset/PolygonShape.h"
#include "Component/AbstractEditCMPT.h"
#include "View/MultiShapesImpl.h"
#include "Render/DrawSelectedShapeVisitor.h"

using namespace wxgui;

SelectShapesOP::SelectShapesOP(EditPanel* editPanel, MultiShapesImpl* shapesImpl,
							   AbstractEditCMPT* callback/* = NULL*/)
	: DrawRectangleOP(editPanel)
	, m_callback(callback)
	, m_shapeImpl(shapesImpl)
	, m_lastCtrlPress(false)
{
	m_selection = shapesImpl->getShapeSelection();
	m_selection->retain();

	m_firstPos.setInvalid();
}

SelectShapesOP::~SelectShapesOP()
{
	clearClipboard();

 	m_selection->clear();
 	m_selection->release();
}

bool SelectShapesOP::onKeyDown(int keyCode)
{
	if (DrawRectangleOP::onKeyDown(keyCode)) return true;

	if (keyCode == WXK_DELETE)
		m_shapeImpl->removeShapeSelection();
	else if (wxGetKeyState(WXK_CONTROL_X))
	{
		clearClipboard();
		m_selection->traverse(FetchAllVisitor<IShape>(m_clipboard));
		for (size_t i = 0, n = m_clipboard.size(); i < n; ++i)
			m_clipboard[i]->retain();
		m_shapeImpl->removeShapeSelection();
	}
	else if (m_lastCtrlPress && (keyCode == 'c' || keyCode == 'C')/*wxGetKeyState(WXK_CONTROL_C)*/)
	{
		clearClipboard();

		std::vector<PolygonShape*> polys;
		m_selection->traverse(FetchAllVisitor<PolygonShape>(polys));
		for (size_t i = 0, n = polys.size(); i < n; ++i)
			m_clipboard.push_back(polys[i]->clone());
	}
	else if (wxGetKeyState(WXK_CONTROL_V))
	{
		// todo: should deep copy
		for (size_t i = 0, n = m_clipboard.size(); i < n; ++i)
		{
			m_clipboard[i]->retain();
			m_shapeImpl->insertShape(m_clipboard[i]);
			m_editPanel->Refresh();
		}
	}

	m_lastCtrlPress = keyCode == WXK_CONTROL;

	return false;
}

bool SelectShapesOP::onMouseLeftDown(int x, int y)
{
	f2Vec2 pos = m_editPanel->transPosScreenToProject(x, y);
	IShape* selected = m_shapeImpl->queryShapeByPos(pos);
	if (selected)
	{
		if (wxGetKeyState(WXK_CONTROL))
		{
			if (m_selection->isExist(selected))
				m_selection->erase(selected);
			else
				m_selection->insert(selected);
		}
		else
		{
			if (!m_selection->isExist(selected))
			{
				m_selection->clear();
				m_selection->insert(selected);
			}
		}
		m_firstPos.setInvalid();

		if (m_callback)
			m_callback->updateControlValue();
	}
	else
	{
		DrawRectangleOP::onMouseLeftDown(x, y);
		m_firstPos = pos;
		m_selection->clear();
		m_editPanel->Refresh();
	}

	return false;
}

bool SelectShapesOP::onMouseLeftUp(int x, int y)
{
	if (DrawRectangleOP::onMouseLeftUp(x, y)) return true;

	if (m_firstPos.isValid())
	{
		f2AABB aabb(m_firstPos, m_editPanel->transPosScreenToProject(x, y));
		std::vector<IShape*> shapes;
		m_shapeImpl->queryShapesByAABB(aabb, shapes);
		for (size_t i = 0, n = shapes.size(); i < n; ++i)
			m_selection->insert(shapes[i]);

		m_firstPos.setInvalid();

		if (m_callback)
			m_callback->updateControlValue();
	}

	return false;
}

bool SelectShapesOP::onDraw() const
{
	if (DrawRectangleOP::onDraw()) return true;

	m_selection->traverse(DrawSelectedShapeVisitor());

	return false;
}

bool SelectShapesOP::clear()
{
	if (DrawRectangleOP::clear()) return true;

	clearClipboard();
	m_selection->clear();
	m_firstPos.setInvalid();

	return false;
}

void SelectShapesOP::clearClipboard()
{
 	for (size_t i = 0, n = m_clipboard.size(); i < n; ++i)
 		m_clipboard[i]->release();
 	m_clipboard.clear();
}