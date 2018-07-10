#include "Control.h"
#include "Blackboard.h"
#include "View.h"
#include "Model.h"
#include "SameColorRegionSelectOp.h"
#include "OutputCoordsOp.h"
#include "Edit/EditComponent/DrawPolylineCmpt.h"

using namespace FEDITOR::EXTRACT_EDGE;

Control::Control()
{
	m_view = new View;
	m_model = new Model(m_view->getBlackboard());

	m_editOp = new OutputCoordsOp(this, static_cast<Model*>(m_model));
}

Control::~Control()
{
}

void Control::onMouseRightDown(int x, int y)
{
	if (m_editOp) 
	{
		bool handled = m_editOp->onMouseRightDown(x, y);
		if (!handled) 
		{
			delete m_editOp;
			Model* model = static_cast<Model*>(m_model);
			assert(model);
			m_editOp = new OutputCoordsOp(this, model);
		}
	}
}

void Control::createEditCmpt()
{
	Model* model = static_cast<Model*>(m_model);
	new DrawPolylineCmpt(this, model->getEditedSprite(), model->getEditedLayer());
}

void Control::handleStep()
{
}

void Control::handleUIEvent()
{
	while (m_view->hasNextEvent())
	{
		Event event = m_view->getNextEvent();
		switch (event.getID())
		{
		case Blackboard::e_OpenFile:
			m_model->handleEvent(event);
			break;

		case Blackboard::e_SetCoordLinesVisible:
			m_model->handleEvent(event);
			break;
		case Blackboard::e_ChangeCoordLines:
			m_model->handleEvent(event);
			break;

		case Blackboard::e_SavePolyline:
			m_model->handleEvent(event);
			break;

		case Blackboard::e_SetColorTol:
			m_model->handleEvent(event);
			break;
		case Blackboard::e_SetEdgeTol:
			m_model->handleEvent(event);
			break;
		case Blackboard::e_AutoSelect:
			m_model->handleEvent(event);
			m_editOp = new SameColorRegionSelectOp(this, static_cast<Model*>(m_model));
			break;
		}
	}
}