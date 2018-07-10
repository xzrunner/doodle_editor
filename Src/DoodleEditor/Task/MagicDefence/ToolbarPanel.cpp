#include "ToolbarPanel.h"
#include "StagePanel.h"
#include "PreviewDialog.h"
#include "SetSpritePropertyCMPT.h"
#include "Blackboard.h"

#include <wx/spinctrl.h>

using namespace deditor::magic_defence;

ToolbarPanel::ToolbarPanel(wxWindow* parent, StagePanel* editPanel,
						   wxgui::LibraryPanel* libraryPanel,
						   wxgui::PropertySettingPanel* propertyPanel)
	: wxgui::ToolbarPanel(parent, editPanel)
	, m_libraryPanel(libraryPanel)
{
	addChild(new wxgui::UniversalCMPT(this, wxT("ճ��Ԫ��"), editPanel, 
		new wxgui::PasteSymbolOP(editPanel, editPanel, libraryPanel)));
	addChild(new wxgui::PasteSpriteCMPT(this, wxT("����ճ��"), editPanel, editPanel, propertyPanel));
	addChild(new SetSpritePropertyCMPT(this, wxT("λ�õ���"), propertyPanel, editPanel));

	SetSizer(initLayout());
}

void ToolbarPanel::setValues(int time, int height)
{
	m_timeSpin->SetValue(time);
	m_heightSpin->SetValue(height);

	Blackboard::time = time;
	Blackboard::length = height;

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
	wxStaticBox* bounding = new wxStaticBox(this, wxID_ANY, wxT("��������"));
	wxBoxSizer* topSizer = new wxStaticBoxSizer(bounding, wxVERTICAL);
	{
		wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
		sizer->Add(new wxStaticText(this, wxID_ANY, wxT("�߶ȣ�")));

		m_heightSpin = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS | wxALIGN_RIGHT, 30, 3000, Blackboard::length);
		Connect(m_heightSpin->GetId(), wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler(ToolbarPanel::onSettingsChanged));
		sizer->Add(m_heightSpin);

		topSizer->Add(sizer);
	}
	topSizer->AddSpacer(10);
	{
		wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
		sizer->Add(new wxStaticText(this, wxID_ANY, wxT("ʱ��(s)��")));

		m_timeSpin = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS | wxALIGN_RIGHT, 6, 600, Blackboard::time);
		Connect(m_timeSpin->GetId(), wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler(ToolbarPanel::onSettingsChanged));
		sizer->Add(m_timeSpin);

		topSizer->Add(sizer);
	}

	return topSizer;
}

wxSizer* ToolbarPanel::initButtonsPanel()
{
	wxSizer* sizer = new wxBoxSizer(wxVERTICAL);

	wxButton* btnPreview = new wxButton(this, wxID_ANY, wxT("Ԥ��"));
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

void ToolbarPanel::onPreview(wxCommandEvent& event)
{
	PreviewDialog dlg(this, static_cast<StagePanel*>(m_editPanel), m_libraryPanel);
	dlg.ShowModal();
	m_editPanel->resetCanvas();
}