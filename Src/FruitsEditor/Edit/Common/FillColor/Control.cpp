#include "Control.h"
#include "Blackboard.h"
#include "View.h"
#include "Model.h"
#include "Edit/EditComponent/LayersMgrCmpt.h"
#include "Edit/EditComponent/DrawPolylineCmpt.h"
#include "Edit/EditComponent/SetColorCmpt.h"
#include "Edit/EditOperation/SelectSpritesOp.h"
#include "Edit/EditOperation/SelectCtlposOp.h"
#include "Edit/MotoX/Utility.h"
#include "Dataset/Layer.h"

using namespace FEDITOR::FILL_COLOR;

Control::Control()
{
	m_view = new View(MOTOX::SCALE_SCREEN_TO_PHYSICS);
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
		if (!handled) setSelectSpritesOp();
	}
}

void Control::createEditCmpt()
{
	m_layersMgrCmpt = new LayersMgrCmpt(m_model->getLayersMgr(), m_view->getCmptMgr(), m_view->getBlackboard());
	Layer* editedLayer = m_layersMgrCmpt->getCertainTypeLayer(LayersMgrCmpt::e_EditedLayer);
	m_drawCmpt = new DrawPolylineCmpt(this, NULL, editedLayer);
	m_setColorCmpt = new SetColorCmpt(m_view->getCmptMgr(), static_cast<Blackboard*>(m_view->getBlackboard())->m_color);
	setSelectSpritesOp();
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
		case Blackboard::e_OpenChains:
			m_model->handleEvent(event);
			break;
		case Blackboard::e_OpenTris:
			m_model->handleEvent(event);
			m_layersMgrCmpt->reloadLayers();
			setSelectSpritesOp();
			break;
		case Blackboard::e_OpenImg:
		case Blackboard::e_OpenFill:
		case Blackboard::e_SaveTris:
		case Blackboard::e_SaveFill:
			m_model->handleEvent(event);
			break;
		case Blackboard::e_SetColor:
			{
				Layer* edited = m_layersMgrCmpt->getCertainTypeLayer(LayersMgrCmpt::e_EditedLayer);
				edited->m_style.m_triangleStyle.color = static_cast<Blackboard*>(m_view->getBlackboard())->m_color;
				m_model->handleEvent(event);
			}
			break;
		case Blackboard::e_ChangeSelectFlag:
			setSelectSpritesOp();
			break;

		case LayersMgrCmpt::e_ChangeEditableLayer:
			{
				Layer* layer = m_layersMgrCmpt->getCertainTypeLayer(LayersMgrCmpt::e_EditedLayer);
				if (layer->getType() == Layer::e_middle)
					m_drawCmpt->setEditedLayer(layer);
				setSelectSpritesOp();
				m_model->getLayersMgr().getSelection().clear();
			}
			break;
		}
	}
}

void Control::setSelectSpritesOp()
{
	Layer* layer = m_layersMgrCmpt->getCertainTypeLayer(LayersMgrCmpt::e_EditedLayer);
	delete m_editOp;
	Blackboard* bb = static_cast<Blackboard*>(m_view->getBlackboard());
	if (bb->m_flagSelectCtlpos == 1)
		m_editOp = new SelectCtlposOp(this, layer);
	else
		m_editOp = new SelectSpritesOp(this, layer, true);
}

std::vector<f2Vec2> Control::getSelectedCtlpos() const
{
	SelectCtlposOp* edit = dynamic_cast<SelectCtlposOp*>(m_editOp);
	if (edit) return edit->getSelectedCtlpos();
	else return std::vector<f2Vec2>();
}