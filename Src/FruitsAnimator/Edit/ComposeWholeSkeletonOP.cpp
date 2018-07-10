#include "ComposeWholeSkeletonOP.h"
#include "View/SkeletonEditPanel.h"
#include "Tools/Render.h"

using namespace FRUITS_ANIMATOR;

ComposeWholeSkeletonOP::ComposeWholeSkeletonOP(SkeletonEditPanel* editPanel, WholeSkeleton* skeleton, 
											   wxTextCtrl* layerTextCtrl)
	: wxgui::ArrangeSpriteOP(editPanel, editPanel)
{
	m_skeleton = skeleton;
	m_selected = NULL;
	m_layerTextCtrl = layerTextCtrl;
}

ComposeWholeSkeletonOP::~ComposeWholeSkeletonOP()
{
	translateToCenter();
}

bool ComposeWholeSkeletonOP::onMouseLeftDown(int x, int y)
{
	if (wxgui::ArrangeSpriteOP::onMouseLeftDown(x, y)) return true;

	f2Vec2 pos = m_editPanel->transPosScreenToProject(x, y);
	m_selected = m_skeleton->queryByPos(pos);

	return false;
}

bool ComposeWholeSkeletonOP::onMouseLeftUp(int x, int y)
{
	if (wxgui::ArrangeSpriteOP::onMouseLeftUp(x, y)) return true;

	if (m_selected)
	{
		absorbSprite(m_selected);
		m_selected->computePosterityAbsoluteCoords();
		m_editPanel->Refresh();
	}

	updateLayerInfo();

	return false;
}

bool ComposeWholeSkeletonOP::onMouseRightUp(int x, int y)
{
	if (wxgui::ArrangeSpriteOP::onMouseRightUp(x, y)) return true;

	if (m_selected) 
	{
		m_selected->computePosterityAbsoluteCoords();
		m_editPanel->Refresh();
	}

	updateLayerInfo();

	return false;
}

bool ComposeWholeSkeletonOP::onDraw() const
{
	if (wxgui::ArrangeSpriteOP::onDraw()) return true;

	if (m_selected) m_selected->drawPosterity();

	return false;
}

void ComposeWholeSkeletonOP::absorbSprite(WholeSkeleton::Sprite* sprite)
{
	if (!m_skeleton->m_root) 
	{
		m_skeleton->m_root = sprite;
		return;
	}
	else if (m_skeleton->m_root == sprite)
	{
		return;
	}

	WholeSkeleton::Sprite* nearest = NULL;
	WholeSkeleton::Node *fromNode = NULL, *toNode = NULL;
	m_skeleton->traverse(NearestNodeVisitor(sprite, &nearest, &fromNode, &toNode));
	assert(nearest && fromNode && toNode);

	f2Vec2 p0 = sprite->getNodeWorldCoords(fromNode),
		p1 = nearest->getNodeWorldCoords(toNode);
	sprite->translate(p1 - p0);
	connect(nearest, sprite, fromNode, toNode);
}

void ComposeWholeSkeletonOP::setSelectedBoneLayer(int layer)
{
	if (m_selected)
	{
		m_selected->setLayer(layer);
		m_editPanel->Refresh();
	}
}

void ComposeWholeSkeletonOP::translateSprite(const f2Vec2& delta)
{
	wxgui::ArrangeSpriteOP::translateSprite(delta);

	if (!m_selected) return;

 	if (m_selected->m_parent)
 	{
 		std::vector<WholeSkeleton::Sprite*>::iterator itr = m_selected->m_parent->m_children.begin();
 		for ( ; itr != m_selected->m_parent->m_children.end(); ++itr)
 		{
 			if (*itr == m_selected)
 			{
 				m_selected->m_parent->m_children.erase(itr);
 				break;
 			}
 		}
 		m_selected->m_parent = NULL;
 	}

 	// todo
 	m_selected->computePosterityAbsoluteCoords();
 	m_editPanel->Refresh();
}

void ComposeWholeSkeletonOP::rotateSprite(const f2Vec2& dst)
{
	if (!m_selected) return;

	if (m_selected->m_parent)
	{
		float angle = f2Math::getAngleInDirection(m_selected->getPosition(), m_lastPos, dst);

		f2Vec2 v0 = f2Math::rotateVector(m_selected->m_relativeCoords.from->pos, m_selected->getAngle());
		f2Vec2 v1 = f2Math::rotateVector(v0, -angle);
		f2Vec2 offset = v1 - v0;
		m_selected->translate(offset);

		m_selected->rotate(angle);

		m_editPanel->Refresh();
	}
	else 
	{
		wxgui::ArrangeSpriteOP::rotateSprite(dst);
	}

 	if (m_selected->m_parent)
 	{
 		m_selected->m_relativeCoords.delta = m_selected->getAngle() - m_selected->m_parent->getAngle();
 	}
 	else
 	{
 		m_selected->m_relativeCoords.delta = m_selected->getAngle();
 	}

 	// todo
 	m_selected->computePosterityAbsoluteCoords();
 	m_editPanel->Refresh();
}

void ComposeWholeSkeletonOP::connect(WholeSkeleton::Sprite* parent, WholeSkeleton::Sprite* child,
									 WholeSkeleton::Node* from, WholeSkeleton::Node* to)
{
	if (child->m_parent != parent)
	{
		if (child->m_parent)
		{
			std::vector<WholeSkeleton::Sprite*>::iterator itr 
				= child->m_parent->m_children.begin();
			for ( ; itr != child->m_parent->m_children.end(); ++itr)
			{
				if (*itr == child)
				{
					child->m_parent->m_children.erase(itr);
					break;
				}
			}

		}
		child->m_parent = parent;
		parent->m_children.push_back(child);
	}

	child->m_relativeCoords.from = from;
	child->m_relativeCoords.to = to;
}

void ComposeWholeSkeletonOP::updateLayerInfo()
{
	m_layerTextCtrl->Clear();
	if (m_selected)
	{
		*m_layerTextCtrl << m_selected->m_layer;
	}
}

void ComposeWholeSkeletonOP::translateToCenter()
{
	if (m_skeleton->m_root)
	{
		AbstractBV* bounding = BVFactory::createBV(e_obb);
		m_skeleton->getBounding(*bounding);
		m_skeleton->m_root->translate(-bounding->center());
		m_skeleton->m_root->computePosterityAbsoluteCoords();
		delete bounding;
	}
}

//////////////////////////////////////////////////////////////////////////
// class ComposeWholeSkeletonOP::NearestNodeVisitor
//////////////////////////////////////////////////////////////////////////

ComposeWholeSkeletonOP::NearestNodeVisitor::
NearestNodeVisitor(WholeSkeleton::Sprite* sprite, WholeSkeleton::Sprite** pResult, 
				   WholeSkeleton::Node** pFromNode, WholeSkeleton::Node** pToNode)
{
	m_sprite = sprite;
	m_pResult = pResult;
	m_pFromNode = pFromNode;
	m_pToNode = pToNode;
	m_nearestDis = FLOAT_MAX;
}

void ComposeWholeSkeletonOP::NearestNodeVisitor::
visit(IObject* object, bool& bFetchNext)
{
	WholeSkeleton::Sprite* toSprite = static_cast<WholeSkeleton::Sprite*>(object);
	if (toSprite == m_sprite)
	{
		bFetchNext = true;
		return;
	}

	const std::vector<WholeSkeleton::Node*> &from = m_sprite->m_body->m_nodes,
		&to = toSprite->m_body->m_nodes;
	for (size_t i = 0, n = from.size(); i < n; ++i)
	{
		for (size_t j = 0, m = to.size(); j < m; ++j)
		{
			f2Vec2 p0 = m_sprite->getNodeWorldCoords(from[i]),
				p1 = toSprite->getNodeWorldCoords(to[j]);
			float dis = f2Math::getDistance(p0, p1);
			if (dis < m_nearestDis)
			{
				m_nearestDis = dis;
				*m_pResult = toSprite;
				*m_pFromNode = from[i];
				*m_pToNode = to[j];
			}
		}
	}

	bFetchNext = true;
}