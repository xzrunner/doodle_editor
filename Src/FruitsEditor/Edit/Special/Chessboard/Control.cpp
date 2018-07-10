#include "Control.h"
#include "View.h"
#include "Model.h"
#include "Blackboard.h"
#include "PasteSpriteCB.h"
#include "ArrangeSpriteCB.h"
#include "Dataset/Layer.h"
#include "Dataset/LayersMgr.h"
#include "Edit/EditOperation/PasteSpriteOp.h"
#include "Edit/EditOperation/ArrangeSpriteOp.h"
#include "File/FileNameParser.h"

using namespace FEDITOR::CHESSBOARD;

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
		case Blackboard::e_openTile:
			openTile(event.getInfo());
			break;
		case Blackboard::e_openLevel:
			m_model->handleEvent(event);
			break;
		case Blackboard::e_saveLevel:
			m_model->handleEvent(event);
			break;
		case Blackboard::e_resizeBg:
			m_model->handleEvent(event);
			break;
		}
	}
}

void Control::openTile(const std::string& filename)
{
	FileNameParser::Type type = FileNameParser::getFileType(filename);
	if (type != FileNameParser::e_img) return;

	Model* model = dynamic_cast<Model*>(m_model);
	Layer *tempLayer = m_model->getLayersMgr().getLayer(Layer::e_uppermost),
		*editedLayer = m_model->getLayersMgr().getLayer(Layer::e_middle);
	if (tempLayer && editedLayer)
	{
		if (m_editOp) delete m_editOp;
		m_editOp = new PasteSpriteOp(this, tempLayer, editedLayer, filename, false,
			new PasteSpriteCB(editedLayer, dynamic_cast<Blackboard*>(m_view->getBlackboard())));
	}
}

void Control::setArrangeSpriteOp()
{
	delete m_editOp;
	Layer* editedLayer = m_model->getLayersMgr().getLayer(Layer::e_middle);
	m_editOp = new ArrangeSpriteOp(this, editedLayer, false,
		new ArrangeSpriteCB(editedLayer, dynamic_cast<Blackboard*>(m_view->getBlackboard())));
}