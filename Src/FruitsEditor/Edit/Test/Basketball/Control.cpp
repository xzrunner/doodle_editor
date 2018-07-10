#include "Control.h"
#include "Blackboard.h"
#include "View.h"
#include "Model.h"
#include "../../EditOperation/ArrangeSpritePhysOp.h"

using namespace FEDITOR::BASKETBALL;

Control::Control()
{
	m_view = new View;
	Model* model = new Model(m_view->getBlackboard(), getWorld());
	m_model = model;

	m_editOp = new ArrangeSpritePhysOp(this, getWorld(), model->getGround());
}

Control::~Control()
{
}

void Control::createEditCmpt()
{
}

void Control::handleStep()
{
	AbstractPhysCtrl::createEditCmpt();
}

void Control::handleUIEvent()
{
	while (m_view->hasNextEvent())
	{
		Event event = m_view->getNextEvent();
		switch (event.getID())
		{
		}
	}
}