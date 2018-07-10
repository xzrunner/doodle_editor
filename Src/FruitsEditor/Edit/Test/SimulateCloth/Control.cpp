#include "Control.h"
#include "Blackboard.h"
#include "View.h"
#include "Model.h"
#include "Edit/EditOperation/ArrangeSpritePhysOp.h"
#include "Edit/EditComponent/DrawPolylineCmpt.h"

using namespace FEDITOR::SIMULATE_CLOTH;

Control::Control()
{
	m_view = new View;
	m_model = new Model(m_view->getBlackboard(), getWorld());
}

Control::~Control()
{
}

void Control::createEditCmpt()
{
	AbstractPhysCtrl::createEditCmpt();
}

void Control::handleStep()
{
	m_model->handleEvent(Blackboard::e_Step);
}

void Control::handleUIEvent()
{
	while (m_view->hasNextEvent())
	{
		Event event = m_view->getNextEvent();
		switch (event.getID())
		{
		case Blackboard::e_openRegularTexture:
			{
				m_model->handleEvent(event);
				Model* model = static_cast<Model*>(m_model);
				m_editOp = new ArrangeSpritePhysOp(this, getWorld(), model->getGround(), ArrangeSpritePhysOp::e_MouseNear);
			}
			break;
		case Blackboard::e_resetWeb:
			m_model->handleEvent(event);
			break;

		case Blackboard::e_resetJointsFrequency:
		case Blackboard::e_resetJointsDamping:
		case Blackboard::e_resetNodesEdge:
			m_model->handleEvent(event);
			break;
		}
	}
}