#include "ToolbarPanel.h"
#include "StagePanel.h"
#include "PartitionCMPT.h"
#include "MeshCMPT.h"

using namespace deditor::texture_edit;

ToolbarPanel::ToolbarPanel(wxWindow* parent, StagePanel* editPanel)
	: wxgui::ToolbarPanel(parent, editPanel)
{
	addChild(new PartitionCMPT(this, wxT("����"), editPanel));
	addChild(new MeshCMPT(this, wxT("mesh"), editPanel));

	SetSizer(initLayout());
}

wxSizer* ToolbarPanel::initLayout()
{
	wxSizer* sizer = new wxBoxSizer(wxVERTICAL);
	sizer->AddSpacer(10);
	{
		wxButton* btn = new wxButton(this, wxID_ANY, wxT("��������..."));
		Connect(btn->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, 
			wxCommandEventHandler(ToolbarPanel::onLoadTexture));
		sizer->Add(btn);
	}
	sizer->AddSpacer(10);
	{
		sizer->Add(initChildrenLayout());
	}
	return sizer;
}

void ToolbarPanel::onLoadTexture(wxCommandEvent& event)
{
	wxFileDialog dlg(this, wxT("ѡ��һ��ͼƬ"), wxEmptyString, wxEmptyString, wxT("*.png;*.jpg;*.bmp"), wxFD_OPEN);
	if (dlg.ShowModal() == wxID_OK)
	{
		static_cast<StagePanel*>(m_editPanel)->loadTexture(dlg.GetPath());
	}
}