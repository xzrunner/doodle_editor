#include "EditPolylineOp.h"
#include "AbstractEditOpCB.h"
#include "../KeyboardTest.h"
#include "../AbstractControl.h"
#include "../EditComponent/NodeCaptureCmpt.h"
#include "../../Dataset/Layer.h"
#include "../../Dataset/LayersMgr.h"
#include "../../Dataset/Sprite.h"

using namespace FEDITOR;

EditPolylineOP::EditPolylineOP(AbstractControl* task, Layer* editable, NodeCaptureCmpt* capture, AbstractEditOpCB* callback/* = NULL*/)
	: AbstractOp(task, NULL, callback)
{
	m_editable = editable;
	m_capture = capture;
	m_firstPos.setInvalid();
	prepareSelectDraw();
}

EditPolylineOP::~EditPolylineOP()
{
	m_tmpLayer->deleteSprite(m_tmpSprite);
}

void EditPolylineOP::onKeyboard(unsigned char key)
{
	switch (key)
	{
	case KEY_DELETE:
		{
			std::set<Sprite*> dirtySet;
			for (size_t i = 0, n = m_batchSelected.size(); i < n; ++i)
			{
				const ChainShapeAddr& sel = m_batchSelected[i];
				sel.shape->erase(sel.iPos);
				dirtySet.insert(sel.sprite);
			}

			std::set<Sprite*>::iterator itr = dirtySet.begin();
			for ( ; itr != dirtySet.end(); ++itr)
				(*itr)->rebuildBounding();

			if (m_callback && !m_batchSelected.empty())
				m_callback->afterKeyboard(key);
		}
		break;
	}
}

void EditPolylineOP::onMouseLeftDown(int x, int y)
{
	f2Vec2 src = getMousePos(x, y);

	const bool capture = m_capture && m_capture->captureByPos(src);
//	if (capture && m_capture->getCapturedAddr().isValid())
	if (capture)
	{
		if (m_capture->getCapturedAddr().layer == m_editable)
		{
			m_selected = m_capture->getCapturedAddr();
			return;
		}
	}

	const bool select = selectPos(src);
	if (!select)
	{
		const bool insert = insertPos(src);
		if (!insert) 
		{
			m_selected.setInvalid();
			m_firstPos = src;
		}
	}
}

void EditPolylineOP::onMouseLeftUp(int x, int y)
{
	m_batchSelected.clear();

	m_lastPos.setInvalid();

	if (m_firstPos.isValid())
	{
		f2AABB aabb(m_firstPos, getMousePos(x, y));
		selectPosByAABB(aabb);

		ChainShape* shape = dynamic_cast<ChainShape*>(m_tmpSprite->popShape());
		assert(shape);
		shape->m_vertices.clear();
		m_tmpSprite->pushShape(shape);

		m_firstPos.setInvalid();
	}

	if (m_callback) m_callback->afterMouseLeftUp(f2Vec2());
}

bool EditPolylineOP::onMouseRightDown(int x, int y)
{
	if (m_capture && m_capture->getCapturedAddr().layer == m_editable)
		m_selected = m_capture->getCapturedAddr();

	if (m_selected.isValid())
	{
		m_selected.shape->erase(m_selected.iPos);
		m_selected.sprite->rebuildBounding();
		m_selected.setInvalid();
		m_capture->clear();
		return true;
	}
	else if (!m_batchSelected.empty())
	{
		m_lastPos = getMousePos(x, y);
	}
	else
	{
		return false;
	}
}

bool EditPolylineOP::onMouseRightUp(int x, int y)
{
	m_lastPos.setInvalid();
	m_batchSelected.clear();

	if (m_callback) m_callback->afterMouseRightUp(f2Vec2());
	return true;
}

void EditPolylineOP::onMouseMove(int x, int y)
{
	const f2Vec2 src = getMousePos(x, y);

	if (m_capture) m_capture->captureByPos(src);
	if (f2Math::getDistance(src, m_selected.getPos()) > getCaptureTolerance())
		m_selected.setInvalid();
}

void EditPolylineOP::onMouseDrag(int x, int y)
{
	if (m_firstPos.isValid())
	{
		f2Vec2 p = getMousePos(x, y);
		m_tmpShape->m_vertices.clear();
		m_tmpShape->pushBack(m_firstPos);
		m_tmpShape->pushBack(f2Vec2(m_firstPos.x, p.y));
		m_tmpShape->pushBack(p);
		m_tmpShape->pushBack(f2Vec2(p.x, m_firstPos.y));
	}

	if (m_selected.isValid())
	{
		m_selected.shape->modify(m_selected.iPos, getMousePos(x, y));
		m_selected.sprite->rebuildBounding();
		if (m_capture) m_capture->refreshPos();
	}
	else if (m_lastPos.isValid() && !m_batchSelected.empty())
	{
		const f2Vec2 curr = getMousePos(x, y);
		for (size_t i = 0, n = m_batchSelected.size(); i < n; ++i)
		{
			ChainShape* shape = m_batchSelected[i].shape;
			int iPos = m_batchSelected[i].iPos;
			shape->m_vertices[iPos] += (curr - m_lastPos);
		}
		m_lastPos = curr;
	}
}

void EditPolylineOP::prepareSelectDraw()
{
	m_tmpLayer = m_task->getLayersMgr().getLayer(Layer::e_uppermost);
	assert(m_tmpLayer);
	m_tmpSprite = new Sprite;
	m_tmpLayer->addSprite(m_tmpSprite);
	m_tmpShape = new ChainShape;
	m_tmpShape->m_isLoop = true;
	m_tmpSprite->pushShape(m_tmpShape);
}

bool EditPolylineOP::selectPos(const f2Vec2& pos)
{
	if (!m_editable) return false;

	const std::vector<Sprite*>& sprites = m_editable->getAllSprites();
	for (size_t i = 0, n = sprites.size(); i < n; ++i)
	{
		const bool select = selectPos(pos, sprites[i]);
		if (select) return true;
	}
	return false;
}

bool EditPolylineOP::selectPos(const f2Vec2& pos, Sprite* sprite)
{
	const std::vector<Shape*>& shapes = sprite->getAllShapes();
	for (size_t i = 0, n = shapes.size(); i < n; ++i)
	{
		const bool select = selectPos(pos, shapes[i]);
		if (select) return true;
	}
	return false;
}

bool EditPolylineOP::selectPos(const f2Vec2& pos, Shape* shape)
{
	if (shape->getType() != e_chain) return false;

	ChainShape* cs = dynamic_cast<ChainShape*>(shape);
	assert(cs);
	size_t iPos;
	const float dis = f2Math::getDisPointToMultiPos(pos, cs->m_vertices, &iPos);
	if (dis < getCaptureTolerance())
	{
		m_selected.shape = cs;
		m_selected.iPos = iPos;
		return true;
	}
	else
		return false;
}

void EditPolylineOP::selectPosByAABB(const f2AABB& aabb)
{
	const std::vector<Sprite*>& sprites = m_editable->getAllSprites();
	for (size_t i = 0, n = sprites.size(); i < n; ++i)
	{
		Sprite* sprite = sprites[i];
		const std::vector<Shape*>& shapes = sprite->getAllShapes();
		for (size_t j = 0, m = shapes.size(); j < m; ++j)
		{
			Shape* shape = shapes[j];
			ChainShape* chain = dynamic_cast<ChainShape*>(shape);
			if (chain)
			{
				for (size_t k = 0, l = chain->m_vertices.size(); k < l; ++k)
				{
					if (f2Math::isPointInAABB(chain->m_vertices[k], aabb))
					{
						ChainShapeAddr addr;
						addr.layer = m_editable;
						addr.sprite = sprite;
						addr.shape = chain;
						addr.iPos = k;
						m_batchSelected.push_back(addr);
					}
				}
			}
		}
	}
}

bool EditPolylineOP::insertPos(const f2Vec2& pos)
{
	if (!m_editable) return false;

	const std::vector<Sprite*>& sprites = m_editable->getAllSprites();
	for (size_t i = 0, n = sprites.size(); i < n; ++i)
	{
		const bool select = insertPos(pos, sprites[i]);
		if (select) return true;
	}
	return false;
}

bool EditPolylineOP::insertPos(const f2Vec2& pos, Sprite* sprite)
{
	const std::vector<Shape*>& shapes = sprite->getAllShapes();
	for (size_t i = 0, n = shapes.size(); i < n; ++i)
	{
		const bool select = insertPos(pos, shapes[i]);
		if (select) return true;
	}
	return false;
}

bool EditPolylineOP::insertPos(const f2Vec2& pos, Shape* shape)
{
	if (shape->getType() != e_chain) return false;

	ChainShape* cs = dynamic_cast<ChainShape*>(shape);
	assert(cs);
	size_t iPos;
	float dis = f2Math::getDisPointToPolyline(pos, cs->m_vertices, &iPos);
	float tol = getCaptureTolerance();
	if (dis < tol)
	{
		cs->insert(iPos + 1, pos);
		m_selected.shape = cs;
		m_selected.iPos = iPos + 1;
		return true;
	}
	else
	{
		dis = f2Math::getDisPointToSegment(pos, cs->m_vertices.front(), cs->m_vertices.back());
		if (dis < tol)
		{
			cs->m_vertices.push_back(pos);
			m_selected.shape = cs;
			m_selected.iPos = cs->m_vertices.size() - 1;
		}
		else
			return false;
	}
}

float EditPolylineOP::getCaptureTolerance() const
{
	if (m_capture) return m_capture->getTolerance();
	else return CAPTURE_TOL;
}