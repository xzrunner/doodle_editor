#include "SelectCtlposOp.h"
#include "Edit/AbstractControl.h"
#include "Dataset/PointShape.h"
#include "Dataset/ChainShape.h"
#include "Dataset/Sprite.h"
#include "Dataset/Layer.h"
#include "Dataset/LayersMgr.h"

using namespace FEDITOR;

SelectCtlposOp::SelectCtlposOp(AbstractControl* task, Layer* editable)
	: AbstractOp(task), m_selection(task->getLayersMgr().getSelection())
{
	m_dataLayer = editable;
	m_firstPos.setInvalid();
	prepareSelectDraw();
}

SelectCtlposOp::~SelectCtlposOp()
{
	m_tmpLayer->deleteSprite(m_tmpSprite);
}

void SelectCtlposOp::onMouseLeftDown(int x, int y)
{
	m_firstPos = getMousePos(x, y);
	m_selection.clear();
}

void SelectCtlposOp::onMouseLeftUp(int x, int y)
{
	if (!m_firstPos.isValid()) return;

	selectCtlpos(f2AABB(m_firstPos, getMousePos(x, y)));

	ChainShape* shape = dynamic_cast<ChainShape*>(m_tmpSprite->popShape());
	assert(shape);
	shape->m_vertices.clear();
	m_tmpSprite->pushShape(shape);

	m_firstPos.setInvalid();
}

bool SelectCtlposOp::onMouseRightDown(int x, int y)
{
	m_selection.clear();
	return true;
}

void SelectCtlposOp::onMouseDrag(int x, int y)
{
	if (!m_firstPos.isValid()) return;

	f2Vec2 p = getMousePos(x, y);
	m_tmpShape->m_vertices.clear();
	m_tmpShape->pushBack(m_firstPos);
	m_tmpShape->pushBack(f2Vec2(m_firstPos.x, p.y));
	m_tmpShape->pushBack(p);
	m_tmpShape->pushBack(f2Vec2(p.x, m_firstPos.y));
}

const std::vector<f2Vec2>& SelectCtlposOp::getSelectedCtlpos() const
{
	return m_selectedCtlpos;
}

void SelectCtlposOp::prepareSelectDraw()
{
	m_tmpLayer = m_task->getLayersMgr().getLayer(Layer::e_uppermost);
	assert(m_tmpLayer);
	m_tmpSprite = new Sprite;
	m_tmpLayer->addSprite(m_tmpSprite);
	m_tmpShape = new ChainShape;
	m_tmpShape->m_isLoop = true;
	m_tmpSprite->pushShape(m_tmpShape);
}

void SelectCtlposOp::selectCtlpos(const f2AABB& aabb)
{
	std::vector<Sprite*> sprites;
	m_dataLayer->queryByAABB(aabb, sprites);

	int maxLen = 0;
	std::vector<f2Vec2> buffer;
	for (size_t i = 0, n = sprites.size(); i < n; ++i)
	{
		Sprite* sprite = sprites[i];
		const std::vector<Shape*>& shapes = sprite->getAllShapes();
		for (size_t i = 0, n = shapes.size(); i < n; ++i)
		{
			ChainShape* chain = dynamic_cast<ChainShape*>(shapes[i]);
			if (chain)
			{
				std::vector<f2Vec2> tmp;
				for (int i = 0, n = chain->m_vertices.size(); i < n; ++i)
				{
					if (f2Math::isPointInAABB(chain->m_vertices[i], aabb))
						tmp.push_back(chain->m_vertices[i]);
				}
				if (tmp.size() > maxLen)
				{
					maxLen = tmp.size();
					buffer.swap(tmp);
				}
			}
		}
	}

	for (size_t i = 0, n = buffer.size(); i < n; ++i)
	{
		Sprite* sprite = new Sprite;
		PointShape* point = new PointShape;
		point->m_pos = buffer[i];
		sprite->pushShape(point);
		m_selection.add(sprite);
		m_selectedCtlpos.push_back(buffer[i]);
	}
}

