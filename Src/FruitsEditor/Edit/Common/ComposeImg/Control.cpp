#include "Control.h"
#include "Blackboard.h"
#include "View.h"
#include "Model.h"
#include "ArrangeSpriteCB.h"
#include "Dataset/Layer.h"
#include "Dataset/LayersMgr.h"
#include "Edit/EditComponent/GuidelinesCmpt.h"
#include "Edit/EditComponent/CoordinateAxesCmpt.h"
#include "Edit/EditOperation/ArrangeSpriteOp.h"
#include "Edit/EditOperation/PasteSpriteOp.h"
#include "File/FileNameParser.h"

using namespace FEDITOR::COMPOSE_IMG;

Control::Control()
{
	m_view = new View;
	m_model = new Model(m_view->getBlackboard());
	m_coordCmpt = NULL;
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
	new GuidelinesCmpt(m_model->getLayersMgr(), m_view->getCmptMgr());
	m_coordCmpt = new CoordinateAxesCmpt(m_model->getLayersMgr(), m_view->getCmptMgr());
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
		case Blackboard::e_OpenBackground:
			m_model->handleEvent(event);
			break;
		case Blackboard::e_OpenTile:
			openTile(event.getInfo());
			break;
		case Blackboard::e_OpenLevel:
			m_model->handleEvent(event);
			break;
		case Blackboard::e_SaveLevel:
			m_model->handleEvent(event);
			break;
		}
	}
}

void Control::openTile(const std::string& filename)
{
	FileNameParser::Type type = FileNameParser::getFileType(filename);
	if (type != FileNameParser::e_img) return;

	Layer *tempLayer = m_model->getLayersMgr().getLayer(Layer::e_uppermost),
		*editedLayer = m_model->getLayersMgr().getLayer(Layer::e_middle);
	if (tempLayer && editedLayer)
	{
		if (m_editOp) delete m_editOp;
		m_editOp = new PasteSpriteOp(this, tempLayer, editedLayer, filename, true);
	}
}

void Control::setArrangeSpriteOp()
{
	delete m_editOp;
	Layer* editedLayer = m_model->getLayersMgr().getLayer(Layer::e_middle);
	assert(m_coordCmpt);
	m_editOp = new ArrangeSpriteOp(this, editedLayer, true, new ArrangeSpriteCB(m_coordCmpt));
}