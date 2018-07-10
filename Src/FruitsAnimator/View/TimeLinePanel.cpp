#include "TimeLinePanel.h"
#include "LayersPanel.h"
#include "KeysPanel.h"
#include "Dataset/Layer.h"
#include "Dataset/LayersMgr.h"
#include <wx/splitter.h>

using namespace FRUITS_ANIMATOR;

const float TimeLinePanel::SASH_GRAVITY_VERT = 0.1f;

TimeLinePanel::TimeLinePanel(wxWindow* parent)
	: wxPanel(parent)
{
	m_layersMgr = new LayersMgr;
	initLayout();
}

TimeLinePanel::~TimeLinePanel()
{
	delete m_layersMgr;
}

void TimeLinePanel::loadFromTextFile(std::ifstream& fin, const LibraryPanel& library)
{
	m_layersMgr->loadFromTextFile(fin, library);
}

void TimeLinePanel::storeToTextFile(std::ofstream& fout, const LibraryPanel& library) const
{
	m_layersMgr->storeToTextFile(fout, library);
}

LayersMgr* TimeLinePanel::getLayerMgr() const
{
	return m_layersMgr;
}

Layer* TimeLinePanel::getCurrLayer() const
{
	return m_layersMgr->getLayer(m_layersPanel->getSelectedLayer());
}

int TimeLinePanel::getCurrFrame() const
{
	return m_keysPanel->getCurrPos();
}

void TimeLinePanel::setStagePanel(StagePanel* stagePanel)
{
	m_keysPanel->setStagePanel(stagePanel);
	m_layersPanel->setStagePanel(stagePanel);
}

int TimeLinePanel::getFPSVal() const
{
	return m_layersPanel->getFPSVal();
}

LayersPanel* TimeLinePanel::getLayersPanel()
{
	return m_layersPanel;
}

KeysPanel* TimeLinePanel::getKeysPanel()
{
	return m_keysPanel;
}

void TimeLinePanel::clear()
{
	m_layersMgr->clear();
	m_keysPanel->setSelectPos(-1, -1);
}

void TimeLinePanel::initLayout()
{
	wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
	initTitle(sizer);
	initSplitterWindow(sizer);
	SetSizer(sizer);
}

void TimeLinePanel::initTitle(wxSizer* sizer)
{
	wxStaticText* title = new wxStaticText(this, wxID_ANY, wxT("Time Line"));
	title->SetForegroundColour(*wxWHITE);
	title->SetBackgroundColour(*wxBLACK);
	sizer->Add(title, 0, wxEXPAND);
}

void TimeLinePanel::initSplitterWindow(wxSizer* sizer)
{
	wxSplitterWindow* splitter = new wxSplitterWindow(this, wxID_ANY);
	m_layersPanel = new LayersPanel(splitter, this, m_layersMgr);
	m_keysPanel = new KeysPanel(splitter, this, m_layersMgr);
	splitter->SetSashGravity(SASH_GRAVITY_VERT);
	splitter->SplitVertically(m_layersPanel, m_keysPanel);
	sizer->Add(splitter, 1, wxEXPAND);
}