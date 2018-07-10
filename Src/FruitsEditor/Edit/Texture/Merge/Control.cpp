#include "Control.h"
#include "View.h"
#include "Model.h"
#include "Blackboard.h"
#include "ArrangeSpriteCB.h"
#include "Edit/EditOperation/ArrangeSpriteOp.h"
#include "File/FileNameParser.h"

using namespace FEDITOR::TEXTURE_MERGE;

Control::Control()
{
	m_view = new View();
	m_model = new Model(m_view->getBlackboard());
}

Control::~Control()
{
}

void Control::onMouseRightDown(int x, int y)
{
	if (m_editOp) 
	{
		bool handled = m_editOp->onMouseRightDown(x, y);
		if (!handled) setArrangeSpriteOp();
	}
}


void Control::createEditCmpt()
{
	setArrangeSpriteOp();
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
		case Blackboard::e_resetBg:
			m_model->handleEvent(event);
			break;
		case Blackboard::e_openTexture:
			m_model->handleEvent(event);
			break;
		case Blackboard::e_saveAsBmp:
		case Blackboard::e_saveAsJpg:
		case Blackboard::e_saveAsPng:
			m_model->handleEvent(event);
			break;
		}
	}
}

void Control::setArrangeSpriteOp()
{
	delete m_editOp;
	Model* model = static_cast<Model*>(m_model);
	Layer* editedLayer = model->getEditedLayer();
	m_editOp = new ArrangeSpriteOp(this, editedLayer, true, new ArrangeSpriteCB(model));
}