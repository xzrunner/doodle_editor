#include "ToolbarPanel.h"
#include "StagePanel.h"
#include "Blackboard.h"
#include "SetSpritePropertyCMPT.h"
#include "PreviewDialog.h"

#include <wx/spinctrl.h>

using namespace deditor::monster;

ToolbarPanel::ToolbarPanel(wxWindow* parent, StagePanel* editPanel,
						   wxgui::LibraryPanel* libraryPanel,
						   wxgui::PropertySettingPanel* propertyPanel)
	: wxgui::ToolbarPanel(parent, editPanel)
	, m_libraryPanel(libraryPanel)
{
	addChild(new wxgui::UniversalCMPT(this, wxT("粘贴元件"), editPanel, 
		new wxgui::PasteSymbolOP(editPanel, editPanel, m_libraryPanel)));
	addChild(new wxgui::PasteSpriteCMPT(this, wxT("批量粘贴"), editPanel, editPanel, propertyPanel));
	addChild(new SetSpritePropertyCMPT(this, wxT("移动位置"), propertyPanel, editPanel));

	SetSizer(initLayout());	
}

void ToolbarPanel::setValues(int time, int height/*, int edge*/,
							 int min, int max)
{
	m_timeSpin->SetValue(time);
	m_heightSpin->SetValue(height);
//	m_edgeSlider->SetValue(edge);
	m_minText->SetValue(wxString::FromDouble(min));
	m_maxText->SetValue(wxString::FromDouble(max));

	Blackboard::time = time;
	Blackboard::length = height;
//	Blackboard::edge = edge;
	Blackboard::min = min;
	Blackboard::max = max;

	m_editPanel->Refresh();
}

wxSizer* ToolbarPanel::initLayout()
{
	wxSizer* sizer = new wxBoxSizer(wxVERTICAL);

	sizer->Add(initSettingPanel());
	sizer->AddSpacer(20);
	sizer->Add(initChildrenLayout());
	sizer->AddSpacer(20);
	sizer->Add(initButtonsPanel());

	return sizer;
}

wxSizer* ToolbarPanel::initSettingPanel()
{
	wxStaticBox* bounding = new wxStaticBox(this, wxID_ANY, wxT("参数设置"));
	wxBoxSizer* topSizer = new wxStaticBoxSizer(bounding, wxVERTICAL);
// 	{
// 		wxStaticBox* bounding = new wxStaticBox(this, wxID_ANY, wxT("格子边长"));
// 		wxBoxSizer* sizer = new wxStaticBoxSizer(bounding, wxVERTICAL);
// 
// 		m_edgeSlider = new wxSlider(this, wxID_ANY, Blackboard::edge, 50, 150);
// 		Connect(m_edgeSlider->GetId(), wxEVT_COMMAND_SLIDER_UPDATED, wxScrollEventHandler(ToolbarPanel::onGridEdgeChanged));
// 		sizer->Add(m_edgeSlider);
// 
// 		topSizer->Add(sizer);
// 	}
// 	topSizer->AddSpacer(10);
	{
		wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
		sizer->Add(new wxStaticText(this, wxID_ANY, wxT("高度：")));
		
		m_heightSpin = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS | wxALIGN_RIGHT, 30, 3000, Blackboard::length);
		Connect(m_heightSpin->GetId(), wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler(ToolbarPanel::onSettingsChanged));
		sizer->Add(m_heightSpin);

		topSizer->Add(sizer);
	}
	topSizer->AddSpacer(10);
	{
		wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
		sizer->Add(new wxStaticText(this, wxID_ANY, wxT("时间(s)：")));

		m_timeSpin = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS | wxALIGN_RIGHT, 6, 600, Blackboard::time);
		Connect(m_timeSpin->GetId(), wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler(ToolbarPanel::onSettingsChanged));
		sizer->Add(m_timeSpin);

		topSizer->Add(sizer);
	}
	topSizer->AddSpacer(20);
	{
		wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
		sizer->Add(new wxStaticText(this, wxID_ANY, wxT("MIN: ")));

		m_minText = new wxTextCtrl(this, wxID_ANY, wxString::FromDouble(Blackboard::min));
		Connect(m_minText->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(ToolbarPanel::onMinMaxValChanged));
		sizer->Add(m_minText);

		topSizer->Add(sizer);
	}
	topSizer->AddSpacer(5);
	{
		wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
		sizer->Add(new wxStaticText(this, wxID_ANY, wxT("MAX: ")));

		m_maxText = new wxTextCtrl(this, wxID_ANY, wxString::FromDouble(Blackboard::max));
		Connect(m_maxText->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(ToolbarPanel::onMinMaxValChanged));
		sizer->Add(m_maxText);

		topSizer->Add(sizer);
	}

	return topSizer;
}

wxSizer* ToolbarPanel::initButtonsPanel()
{
	wxSizer* sizer = new wxBoxSizer(wxVERTICAL);

	wxButton* btnPreview = new wxButton(this, wxID_ANY, wxT("预览"));
	Connect(btnPreview->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(ToolbarPanel::onPreview));
	sizer->Add(btnPreview);

	return sizer;
}

void ToolbarPanel::onGridEdgeChanged(wxScrollEvent& event)
{
	Blackboard::edge = event.GetInt();
	static_cast<StagePanel*>(m_editPanel)->updateAllSpritesLocation();
	m_editPanel->Refresh();
}

void ToolbarPanel::onSettingsChanged(wxSpinEvent& event)
{
	Blackboard::length = m_heightSpin->GetValue();
	Blackboard::time = m_timeSpin->GetValue();
	
	m_editPanel->Refresh();
}

void ToolbarPanel::onMinMaxValChanged(wxCommandEvent& event)
{
	Blackboard::min = wxVariant(m_minText->GetLineText(0)).GetInteger();
	Blackboard::max = wxVariant(m_maxText->GetLineText(0)).GetInteger();
}

void ToolbarPanel::onPreview(wxCommandEvent& event)
{
	PreviewDialog dlg(this, static_cast<StagePanel*>(m_editPanel), m_libraryPanel);
	dlg.ShowModal();
	m_editPanel->resetCanvas();
}