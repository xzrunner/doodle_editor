#include "ToolbarPanel.h"
#include "StagePanel.h"
#include "Blackboard.h"

#include <wx/spinctrl.h>

using namespace deditor::shoot_bubble;

ToolbarPanel::ToolbarPanel(wxWindow* parent, StagePanel* editPanel,
						   wxgui::LibraryPanel* libraryPanel,
						   wxgui::PropertySettingPanel* propertyPanel)
	: wxgui::ToolbarPanel(parent, editPanel)
{
	addChild(new wxgui::UniversalCMPT(this, wxT("粘贴元件"), editPanel, 
		new wxgui::PasteSymbolOP(editPanel, editPanel, libraryPanel)));
	addChild(new wxgui::PasteSpriteCMPT(this, wxT("批量粘贴"), editPanel, editPanel, propertyPanel));
	addChild(new wxgui::UniversalCMPT(this, wxT("移动位置"), editPanel, 
		new wxgui::ArrangeSpriteFixOP(editPanel, editPanel, propertyPanel)));

	SetSizer(initLayout());	
}

wxSizer* ToolbarPanel::initLayout()
{
	wxStaticBox* bounding = new wxStaticBox(this, wxID_ANY, wxT("参数设置"));
	wxBoxSizer* topSizer = new wxStaticBoxSizer(bounding, wxVERTICAL);

	{
		wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
		sizer->Add(new wxStaticText(this, wxID_ANY, wxT("行数：")));

		m_row = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(50, -1), 
			wxSP_ARROW_KEYS, 2, 30, 20);
		Connect(m_row->GetId(), wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler(ToolbarPanel::onParamsChanged));
		sizer->Add(m_row);

		topSizer->Add(sizer);
	}
	topSizer->AddSpacer(10);
	{
		wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
		sizer->Add(new wxStaticText(this, wxID_ANY, wxT("列数：")));

		m_col = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(50, -1), 
			wxSP_ARROW_KEYS, 2, 20, 10);
		Connect(m_col->GetId(), wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler(ToolbarPanel::onParamsChanged));
		sizer->Add(m_col);

		topSizer->Add(sizer);
	}
	topSizer->AddSpacer(20);
	{
		wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
		sizer->Add(new wxStaticText(this, wxID_ANY, wxT("边长：")));

		m_edge = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(50, -1), 
			wxSP_ARROW_KEYS, 16, 512, 64);
		Connect(m_edge->GetId(), wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler(ToolbarPanel::onParamsChanged));
		sizer->Add(m_edge);

		topSizer->Add(sizer);
	}
	onParamsChanged(wxSpinEvent());
	topSizer->AddSpacer(20);
	topSizer->Add(initChildrenLayout());

	return topSizer;
}

void ToolbarPanel::onParamsChanged(wxSpinEvent& event)
{
	bool reset = Blackboard::edge != m_edge->GetValue();

	Blackboard::row = m_row->GetValue();
	Blackboard::col = m_col->GetValue();
	Blackboard::edge = m_edge->GetValue();

	if (reset)
		static_cast<StagePanel*>(m_editPanel)->updateAllSpritesLocation();

	m_editPanel->Refresh();
}