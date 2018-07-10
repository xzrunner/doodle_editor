#include "ToolbarPanel.h"
#include "StagePanel.h"
#include "Blackboard.h"

using namespace deditor::boundary_extraction;

ToolbarPanel::ToolbarPanel(wxWindow* parent, StagePanel* editPanel)
	: wxgui::ToolbarPanel(parent, editPanel)
{
	addChild(new wxgui::DrawLineCMPT(this, wxT("描边"), editPanel, editPanel));

	SetSizer(initLayout());	
}

void ToolbarPanel::changeCurrItem(LibraryItem* item)
{
	
}

wxSizer* ToolbarPanel::initLayout()
{
	wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
	{
		wxCheckBox* closeCheck = new wxCheckBox(this, wxID_ANY, wxT("曲线闭合"));
		closeCheck->SetValue(Blackboard::isClosed);
		Connect(closeCheck->GetId(), wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(ToolbarPanel::onSetClose));
		sizer->Add(closeCheck);

	}
	sizer->AddSpacer(20);
	sizer->Add(initChildrenLayout());
	sizer->AddSpacer(20);
	{
		wxButton* btnClear = new wxButton(this, wxID_ANY, wxT("清除曲线"));
		Connect(btnClear->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, 
			wxCommandEventHandler(ToolbarPanel::onClearLines));
		sizer->Add(btnClear);

	}
	return sizer;
}

void ToolbarPanel::onSetClose(wxCommandEvent& event)
{
	Blackboard::isClosed = event.IsChecked();
}

void ToolbarPanel::onClearLines(wxCommandEvent& event)
{
	static_cast<StagePanel*>(m_editPanel)->clearItemLines();
	m_editPanel->Refresh();
}