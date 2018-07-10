#include "BackstagePanel.h"
#include "SrcPanel.h"
#include "DstPanel.h"
#include "Dataset/DataConnection.h"
#include <wx/splitter.h>

using namespace GAME_FRUITS;
using namespace GAME_FRUITS::VIEW;

const float BackstagePanel::SASH_GRAVITY_HOR = 0.8f;

BackstagePanel::BackstagePanel(wxWindow* parent)
	: wxPanel(parent)
{
	initLayout();
}

void BackstagePanel::initLayout()
{
	wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
	initTitle(sizer);
	initSplitterWindow(sizer);
	SetSizer(sizer);
}

void BackstagePanel::initTitle(wxSizer* sizer)
{
	wxStaticText* title = new wxStaticText(this, wxID_ANY, wxT("Backstage"));
	title->SetForegroundColour(*wxWHITE);
	title->SetBackgroundColour(*wxBLACK);
	sizer->Add(title, 0, wxEXPAND);
}

void BackstagePanel::initSplitterWindow(wxSizer* sizer)
{
	wxSplitterWindow* splitter = new wxSplitterWindow(this, wxID_ANY);
	BACKSTAGE::SrcPanel* srcPanel = new BACKSTAGE::SrcPanel(splitter);
	BACKSTAGE::DstPanel* dstPanel = new BACKSTAGE::DstPanel(splitter);
	splitter->SetSashGravity(SASH_GRAVITY_HOR);
	splitter->SplitHorizontally(dstPanel, srcPanel);
	sizer->Add(splitter, 1, wxEXPAND);

	DataConnection::m_dstPanel = dstPanel;
}