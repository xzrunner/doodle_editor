#include "Control.h"
#include "View.h"
#include "Model.h"
#include "Blackboard.h"
#include "PasteSpriteCB.h"
#include "Edit/EditOperation/ArrangeSpriteOp.h"
#include "Edit/EditOperation/PasteSpriteOp.h"
#include "Edit/EditComponent/LayersMgrCmpt.h"
#include "Edit/EditComponent/PasteSpriteSetCmpt.h"
#include "Edit/EditComponent/GuidelinesLongCmpt.h"
#include "Edit/EditComponent/DrawPolylineCmpt.h"
#include "File/FileNameParser.h"

using namespace FEDITOR::SKATER;

Control::Control()
{
	m_view = new View();
	m_model = new Model(m_view->getBlackboard());

	m_layersMgrCmpt = NULL;
	m_pasteSpriteSetCmpt = NULL;
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
	m_layersMgrCmpt = new LayersMgrCmpt(m_model->getLayersMgr(), m_view->getCmptMgr(), m_view->getBlackboard());
	m_pasteSpriteSetCmpt = new PasteSpriteSetCmpt(m_view->getCmptMgr());
	new GuidelinesLongCmpt(m_model->getLayersMgr(), m_view->getCmptMgr());

	Model* model = static_cast<Model*>(m_model);
	new DrawPolylineCmpt(this, model->getTrackSprite(), model->getTrackLayer());

	setArrangeSpriteOp();

	static_cast<Model*>(m_model)->setLayersMgrCmpt(m_layersMgrCmpt);
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
		case Blackboard::e_OpenOldVersion:
			m_model->handleEvent(event);
			break;
		case Blackboard::e_OpenBound:
			m_model->handleEvent(event);
			break;
		case Blackboard::e_SaveLevel:
			m_model->handleEvent(event);
			break;
		case Blackboard::e_SaveTrack:
			m_model->handleEvent(event);
			break;
		case Blackboard::e_SetTexCoords:
			m_model->handleEvent(event);
			break;

		case LayersMgrCmpt::e_ChangeEditableLayer:
			setArrangeSpriteOp();
			m_model->getLayersMgr().getSelection().clear();
			break;
		}
	}
}

void Control::openTile(const std::string& filename)
{
	FileNameParser::Type type = FileNameParser::getFileType(filename);
	if (type != FileNameParser::e_img) return;

	Layer *tempLayer = m_layersMgrCmpt->getCertainTypeLayer(LayersMgrCmpt::e_TempLayer),
		*editedLayer = m_layersMgrCmpt->getCertainTypeLayer(LayersMgrCmpt::e_EditedLayer);
	if (tempLayer && editedLayer)
	{
		if (m_editOp) delete m_editOp;
		float xScale, yScale;
		m_pasteSpriteSetCmpt->getScale(xScale, yScale);
		PasteSpriteCB* callback = new PasteSpriteCB(dynamic_cast<Model*>(m_model)->getBoundsContainer());
		m_editOp = new PasteSpriteOp(this, tempLayer, editedLayer, filename, true, callback, xScale, yScale);
	}
}

void Control::setArrangeSpriteOp()
{
	delete m_editOp;
	Layer* editedLayer = m_layersMgrCmpt->getCertainTypeLayer(LayersMgrCmpt::e_EditedLayer);
	m_editOp = new ArrangeSpriteOp(this, editedLayer, true);
}