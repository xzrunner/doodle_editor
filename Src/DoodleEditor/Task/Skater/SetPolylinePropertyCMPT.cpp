#include "SetPolylinePropertyCMPT.h"
#include "StagePanel.h"

using namespace deditor::skater;

SetPolylinePropertyCMPT::SetPolylinePropertyCMPT(wxWindow* parent, const wxString& name,
												 StagePanel* editPanel)
	: wxgui::AbstractEditCMPT(parent, name, editPanel)
{
	m_editOP = new wxgui::SelectShapesOP(editPanel, editPanel, this);
}

void SetPolylinePropertyCMPT::updateControlValue()
{
	wxgui::ShapeSelection* selection = static_cast<StagePanel*>(m_editPanel)->getShapeSelection();
	if (!selection->empty())
	{
		GetChainCloseVisitor closeVisitor;
		selection->traverse(closeVisitor);
		switch (closeVisitor.getType())
		{
		case GetChainCloseVisitor::e_open:
			m_closeCtrl->Set3StateValue(wxCHK_UNCHECKED);
			break;
		case GetChainCloseVisitor::e_close:
			m_closeCtrl->Set3StateValue(wxCHK_CHECKED);
			break;
		case GetChainCloseVisitor::e_uncertain:
			m_closeCtrl->Set3StateValue(wxCHK_UNDETERMINED);
			break;
		}

		GetChainIDVisitor idVisitor;
		selection->traverse(idVisitor);
		if (idVisitor.getID() == INT_MAX)
			m_idCtrl->SetValue(wxT(""));
		else
			m_idCtrl->SetValue(wxString::FromDouble(idVisitor.getID()));
	}
	else
	{
		m_closeCtrl->Set3StateValue(wxCHK_UNCHECKED);
		m_idCtrl->SetValue(wxT(""));
	}
}

wxSizer* SetPolylinePropertyCMPT::initLayout()
{
	wxStaticBox* bounding = new wxStaticBox(this, wxID_ANY, wxT("ÊôÐÔÉèÖÃ"));
	wxBoxSizer* sizer = new wxStaticBoxSizer(bounding, wxVERTICAL);

	m_closeCtrl = new wxCheckBox(this, wxID_ANY, wxT("±ÕºÏ"), wxDefaultPosition, wxDefaultSize, wxCHK_3STATE);
	m_closeCtrl->SetValue(false);
	Connect(m_closeCtrl->GetId(), wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(SetPolylinePropertyCMPT::onChangeCloseType));
	sizer->Add(m_closeCtrl);

	sizer->AddSpacer(8);

	wxBoxSizer* idSizer = new wxBoxSizer(wxHORIZONTAL);
	idSizer->Add(new wxStaticText(this, wxID_ANY, wxT("ID: ")));
	m_idCtrl = new wxTextCtrl(this, wxID_ANY, wxEmptyString);
	Connect(m_idCtrl->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(SetPolylinePropertyCMPT::onChangeID));
	idSizer->Add(m_idCtrl);
	sizer->Add(idSizer);

	return sizer;
}

void SetPolylinePropertyCMPT::onChangeCloseType(wxCommandEvent& event)
{
	wxgui::ShapeSelection* selection = static_cast<StagePanel*>(m_editPanel)->getShapeSelection();
	if (!selection->empty())
		selection->traverse(SetChainCloseVisitor(event.IsChecked()));
	m_editPanel->Refresh();
}

void SetPolylinePropertyCMPT::onChangeID(wxCommandEvent& event)
{
	wxgui::ShapeSelection* selection = static_cast<StagePanel*>(m_editPanel)->getShapeSelection();
	if (!selection->empty())
	{
		wxVariant vx = event.GetString();
		selection->traverse(SetChainIDVisitor(vx.GetInteger()));
	}
}

//////////////////////////////////////////////////////////////////////////
// class SetPolylinePropertyCMPT::GetChainCloseVisitor
//////////////////////////////////////////////////////////////////////////

SetPolylinePropertyCMPT::GetChainCloseVisitor::
GetChainCloseVisitor()
{
	m_type = e_uncertain;
}

void SetPolylinePropertyCMPT::GetChainCloseVisitor::
visit(IObject* object, bool& bFetchNext)
{
	wxgui::ChainShape* chain = static_cast<wxgui::ChainShape*>(object);
	if (m_type == e_uncertain)
	{
		m_type = chain->isClosed() ? e_close : e_open;
		bFetchNext = true;
	}
	else if ((m_type == e_close && !chain->isClosed())
		|| m_type == e_open && chain->isClosed())
	{
		m_type = e_uncertain;
		bFetchNext = false;
	}
	else 
	{
		bFetchNext = true;
	}
}

//////////////////////////////////////////////////////////////////////////
// class SetPolylinePropertyCMPT::GetChainIDVisitor
//////////////////////////////////////////////////////////////////////////

SetPolylinePropertyCMPT::GetChainIDVisitor::
GetChainIDVisitor()
{
	m_id = INT_MAX;
}

void SetPolylinePropertyCMPT::GetChainIDVisitor::
visit(IObject* object, bool& bFetchNext)
{
	wxgui::IShape* shape = static_cast<wxgui::IShape*>(object);
	int* userData = static_cast<int*>(shape->getUserData());
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
// class SetPolylinePropertyCMPT::SetChainCloseVisitor
//////////////////////////////////////////////////////////////////////////

SetPolylinePropertyCMPT::SetChainCloseVisitor::
SetChainCloseVisitor(bool bClose)
{
	m_bClose = bClose;
}

void SetPolylinePropertyCMPT::SetChainCloseVisitor::
visit(IObject* object, bool& bFetchNext)
{
	wxgui::ChainShape* chain = static_cast<wxgui::ChainShape*>(object);
	chain->setClosed(m_bClose);

	bFetchNext = true;
}

//////////////////////////////////////////////////////////////////////////
// class SetPolylinePropertyCMPT::SetChainIDVisitor
//////////////////////////////////////////////////////////////////////////

SetPolylinePropertyCMPT::SetChainIDVisitor::
SetChainIDVisitor(int id)
{
	m_id = id;
}

void SetPolylinePropertyCMPT::SetChainIDVisitor::
visit(IObject* object, bool& bFetchNext)
{
 	wxgui::IShape* shape = static_cast<wxgui::IShape*>(object);
 	int* userData = static_cast<int*>(shape->getUserData());
 	userData[0] = m_id;

	bFetchNext = true;
}