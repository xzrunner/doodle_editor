#include "LayersPanel.h"
#include "LayersPropertyWidget.h"
#include "LayersContentWidget.h"
#include "TimeLinePanel.h"
#include "KeysPanel.h"
#include "Utility.h"
#include "StagePanel.h"
#include "Dataset/LayersMgr.h"

using namespace FRUITS_ANIMATOR;

LayersPanel::LayersPanel(wxWindow* parent, TimeLinePanel* timeLinePanel, LayersMgr* layersMgr)
	: wxPanel(parent)
{
	m_timeLinePanel = timeLinePanel;
	m_layersMgr = layersMgr;
	m_stagePanel = NULL;
	initLayout();

	m_selected = -1;
}

void LayersPanel::onAddLayer()
{
	m_selected = m_layersMgr->size();
	m_layersMgr->insertNewLayer();
	m_parent->Refresh();
}

void LayersPanel::onDelLayer()
{
	m_stagePanel->removeSpriteSelection();
	m_layersMgr->deleteLayer(m_selected);
	if (m_layersMgr->size() == 0) m_selected = -1;
	else if (m_selected > 0) --m_selected;
	KeysPanel* keysPanel = m_timeLinePanel->getKeysPanel();
	keysPanel->setCurrPos(keysPanel->getCurrPos());
	m_timeLinePanel->Refresh();

	m_stagePanel->loadCurrFrameSprites();
}

void LayersPanel::onPlay()
{
// 	KeysPanel* keysPanel = m_timeLinePanel->getKeysPanel();
// 	int last = keysPanel->getCurrPos();
// 	do 
// 	{
// 		keysPanel->setCurrPos(++last);
// //		Sleep(1000.0f / 24);
// 	} while (keysPanel->getCurrPos() == last);
}

void LayersPanel::setSelectedLayer(int index)
{
	if (m_selected != index && index < m_layersMgr->size())
	{
		m_selected = index;
		m_contentWidget->Refresh();
	}
}

int LayersPanel::getSelectedLayer() const
{
	return m_selected;
}

void LayersPanel::setStagePanel(StagePanel* stagePanel)
{
	m_stagePanel = stagePanel;
}

void LayersPanel::refreshKeysPanel() const
{
	m_timeLinePanel->getKeysPanel()->Refresh();
}

int LayersPanel::getFPSVal() const
{
	return m_propertyWidget->getFPSVal();
}

void LayersPanel::initLayout()
{
	wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
	m_propertyWidget = new LayersPropertyWidget(this);
	sizer->Add(m_propertyWidget, 0, wxALIGN_LEFT);
	m_contentWidget = new LayersContentWidget(this, wxID_ANY, m_layersMgr);
	sizer->Add(m_contentWidget, 1, wxEXPAND);
	SetSizer(sizer);
}