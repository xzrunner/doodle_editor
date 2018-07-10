#include "SelectJointOP.h"
#include "BodyData.h"
#include "DrawUtils.h"
#include "RevoluteJoint.h"
#include "PrismaticJoint.h"
#include "DistanceJoint.h"
#include "WheelJoint.h"
#include "StagePanel.h"
#include "JointPropertySetting.h"

using namespace deditor::modeling;

SelectJointOP::SelectJointOP(wxgui::EditPanel* editPanel, 
							 wxgui::MultiSpritesImpl* spritesImpl, 
							 wxgui::PropertySettingPanel* propertyPanel, 
							 wxgui::AbstractEditCMPT* callback /*= NULL*/)
	: SelectBodyOP(editPanel, spritesImpl, propertyPanel, callback)
	, m_mouseOn(NULL)
	, m_selected(NULL)
{
}

bool SelectJointOP::onKeyDown(int keyCode)
{
	if (SelectBodyOP::onKeyDown(keyCode)) return true;

	if (keyCode == WXK_DELETE && m_selected)
	{
		if (m_mouseOn == m_selected) m_mouseOn = NULL;
		static_cast<StagePanel*>(m_editPanel)->removeJoint(m_selected);
		m_selected = NULL;
		m_editPanel->Refresh();
	}

	return false;
}

bool SelectJointOP::onMouseLeftDown(int x, int y)
{
	f2Vec2 pos = m_editPanel->transPosScreenToProject(x, y);
	JointData* joint = static_cast<StagePanel*>(m_editPanel)->queryJointByPos(pos);
	if (joint && !m_selected || !joint && m_selected)
		m_editPanel->Refresh();

	m_selected = joint;

	if (m_selected)
	{
		m_propertyPanel->setPropertySetting(new JointPropertySetting(m_editPanel, m_selected));
		m_selection->clear();
	}
	else
	{
		m_propertyPanel->setPropertySetting(NULL);
		SelectBodyOP::onMouseLeftDown(x, y);
	}

	return false;
}

bool SelectJointOP::onMouseLeftUp(int x, int y)
{
	if (SelectBodyOP::onMouseLeftUp(x, y)) return true;

	if (m_selected)
		m_propertyPanel->setPropertySetting(new JointPropertySetting(m_editPanel, m_selected));
	else
		m_propertyPanel->setPropertySetting(NULL);

	return false;
}

bool SelectJointOP::onMouseMove(int x, int y)
{
	if (SelectBodyOP::onMouseMove(x, y)) 
		return true;

	f2Vec2 pos = m_editPanel->transPosScreenToProject(x, y);
	JointData* joint = static_cast<StagePanel*>(m_editPanel)->queryJointByPos(pos);
	if (joint && !m_mouseOn || !joint && m_mouseOn)
		m_editPanel->Refresh();

	m_mouseOn = joint;

	return false;
}

bool SelectJointOP::onMouseDrag(int x, int y)
{
	if (SelectBodyOP::onMouseDrag(x, y)) 
		return true;

	if (m_selected)
	{
		f2Vec2 pos = m_editPanel->transPosScreenToProject(x, y);
		switch (m_selected->type)
		{
		case JointData::e_revoluteJoint:
			{
				RevoluteJoint* joint = static_cast<RevoluteJoint*>(m_selected);
				const float disA = f2Math::getDistance(pos, joint->getWorldAnchorA()),
					disB = f2Math::getDistance(pos, joint->getWorldAnchorB());
				if (disA < disB)
					joint->setLocalAnchorA(pos);
				else
					joint->setLocalAnchorB(pos);
			}
			break;
		case JointData::e_prismaticJoint:
			{
				PrismaticJoint* joint = static_cast<PrismaticJoint*>(m_selected);
				const float disA = f2Math::getDistance(pos, joint->getWorldAnchorA()),
					disB = f2Math::getDistance(pos, joint->getWorldAnchorB());
				if (disA < disB)
					joint->setLocalAnchorA(pos);
				else
					joint->setLocalAnchorB(pos);
			}
			break;
		case JointData::e_distanceJoint:
			{
				DistanceJoint* joint = static_cast<DistanceJoint*>(m_selected);
				const float disA = f2Math::getDistance(pos, joint->getWorldAnchorA()),
					disB = f2Math::getDistance(pos, joint->getWorldAnchorB());
				if (disA < disB)
					joint->setLocalAnchorA(pos);
				else
					joint->setLocalAnchorB(pos);
			}
			break;
		case JointData::e_wheelJoint:
			{
				WheelJoint* joint = static_cast<WheelJoint*>(m_selected);
				const float disA = f2Math::getDistance(pos, joint->getWorldAnchorA()),
					disB = f2Math::getDistance(pos, joint->getWorldAnchorB());
				if (disA < disB)
					joint->setLocalAnchorA(pos);
				else
					joint->setLocalAnchorB(pos);
			}
			break;
		}

		m_editPanel->Refresh();
	}

	return false;
}

bool SelectJointOP::onDraw() const
{
	if (SelectBodyOP::onDraw()) 
		return true;

	m_selection->traverse(DrawSelectedVisitor());

	if (m_mouseOn)
		m_mouseOn->draw(JointData::e_mouseOn);
	if (m_selected) 
		m_selected->draw(JointData::e_selected);

	return false;
}

bool SelectJointOP::clear()
{
	if (SelectBodyOP::onDraw()) 
		return true;

	m_selected = m_mouseOn = NULL;

	return false;
}

wxgui::IPropertySetting* SelectJointOP::createPropertySetting(wxgui::ISprite* sprite) const
{
	return NULL;
}

void SelectJointOP::DrawSelectedVisitor::
visit(IObject* object, bool& bFetchNext) 
{
	std::vector<f2Vec2> bound;
	wxgui::ISprite* sprite = static_cast<wxgui::ISprite*>(object);
	BodyData* body = static_cast<BodyData*>(sprite->getUserData());
	DrawUtils::drawBody(body, DrawUtils::e_selected);
	bFetchNext = true;
}