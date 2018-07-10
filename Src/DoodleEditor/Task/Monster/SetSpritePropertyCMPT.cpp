#include "SetSpritePropertyCMPT.h"
#include "StagePanel.h"

using namespace deditor::monster;

SetSpritePropertyCMPT::SetSpritePropertyCMPT(wxWindow* parent, const wxString& name,
											 wxgui::PropertySettingPanel* propertyPanel,
											 StagePanel* editPanel)
	: wxgui::AbstractEditCMPT(parent, name, editPanel)
	, m_editPanel(editPanel)
{
	m_editOP = new wxgui::ArrangeSpriteFixOP(editPanel, editPanel, propertyPanel, this);
}

void SetSpritePropertyCMPT::updateControlValue()
{
	wxgui::SpriteSelection* selection = m_editPanel->getSpriteSelection();
	if (!selection->empty())
	{
		GetSpriteIDVisitor idVisitor;
		selection->traverse(idVisitor);
		if (idVisitor.getID() == INT_MAX)
			m_idCtrl->SetValue(wxT(""));
		else
			m_idCtrl->SetValue(wxString::FromDouble(idVisitor.getID()));
	}
	else
	{
		m_idCtrl->SetValue(wxT(""));
	}
}

wxSizer* SetSpritePropertyCMPT::initLayout()
{
	wxStaticBox* bounding = new wxStaticBox(this, wxID_ANY, wxT("ÊôÐÔÉèÖÃ"));
	wxBoxSizer* sizer = new wxStaticBoxSizer(bounding, wxVERTICAL);

	wxBoxSizer* idSizer = new wxBoxSizer(wxHORIZONTAL);
	idSizer->Add(new wxStaticText(this, wxID_ANY, wxT("ID: ")));
	m_idCtrl = new wxTextCtrl(this, wxID_ANY, wxEmptyString);
	Connect(m_idCtrl->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(SetSpritePropertyCMPT::onChangeID));
	idSizer->Add(m_idCtrl);
	sizer->Add(idSizer);

	return sizer;
}

void SetSpritePropertyCMPT::onChangeID(wxCommandEvent& event)
{
	wxgui::SpriteSelection* selection = m_editPanel->getSpriteSelection();
	if (!selection->empty())
	{
		wxVariant vx = event.GetString();
		selection->traverse(SetSpriteIDVisitor(vx.GetInteger()));
	}
}

//////////////////////////////////////////////////////////////////////////
// class SetSpritePropertyCMPT::GetSpriteIDVisitor
//////////////////////////////////////////////////////////////////////////

SetSpritePropertyCMPT::GetSpriteIDVisitor::
GetSpriteIDVisitor()
	: m_id(INT_MAX)
{
}

void SetSpritePropertyCMPT::GetSpriteIDVisitor::
visit(IObject* object, bool& bFetchNext)
{
	wxgui::ISprite* sprite = static_cast<wxgui::ISprite*>(object);
	float* userData = static_cast<float*>(sprite->getUserData());
	if (m_id == INT_MAX) 
	{
		m_id = userData[0];
		bFetchNext = true;
	}
	else
	{
		if (m_id != userData[0])
		{
			m_id = INT_MAX;
			bFetchNext = false;
		}
		else
			bFetchNext = true;
	}
}

//////////////////////////////////////////////////////////////////////////
// class SetPolylinePropertyCMPT::SetSpriteIDVisitor
//////////////////////////////////////////////////////////////////////////

SetSpritePropertyCMPT::SetSpriteIDVisitor::
SetSpriteIDVisitor(int id)
	: m_id(id)
{
}

void SetSpritePropertyCMPT::SetSpriteIDVisitor::
visit(IObject* object, bool& bFetchNext)
{
	wxgui::ISprite* sprite = static_cast<wxgui::ISprite*>(object);
	float* userData = static_cast<float*>(sprite->getUserData());
	userData[0] = m_id;

	bFetchNext = true;
}