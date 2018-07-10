#include "TrackChainEditCMPT.h"
#include "StagePanel.h"
#include "TrackChain.h"

#include <wx/spinctrl.h>

using namespace deditor::motox;

TrackChainEditCMPT::TrackChainEditCMPT(wxWindow* parent, const wxString& name,
									   StagePanel* editPanel)
	: AbstractEditCMPT(parent, name, editPanel)
	, m_editPanel(editPanel)
{
	addChild(new wxgui::EditNodesCMPT(this, wxT("±à¼­½Úµã"), editPanel, editPanel));
	addChild(new wxgui::EditPolylinesCMPT(this, wxT("±à¼­Ïß"), editPanel, editPanel));
}

wxSizer* TrackChainEditCMPT::initLayout()
{
	wxSizer* sizer = new wxBoxSizer(wxVERTICAL);
	sizer->Add(initChildrenLayout());
	return sizer;
}

void TrackChainEditCMPT::onSetScale(wxCommandEvent& event)
{
	const float scale = wxVariant(event.GetString()).GetInteger() * 0.01f;
	m_editPanel->traverseShapes(ScaleVisitor(scale), wxgui::e_editable);
	m_editPanel->Refresh();
}

void TrackChainEditCMPT::onSetOffset(wxSpinEvent& event)
{
	wxgui::ShapeSelection* selection = m_editPanel->getShapeSelection();
	if (!selection->empty())
		selection->traverse(TranslationVisitor(f2Vec2(m_xOffset->GetValue(), m_yOffset->GetValue())));
	m_editPanel->Refresh();
}

//////////////////////////////////////////////////////////////////////////
// class TrackChainEditCMPT::ScaleVisitor
//////////////////////////////////////////////////////////////////////////

void TrackChainEditCMPT::ScaleVisitor::
visit(IObject* object, bool& bFetchNext)
{
	TrackChain* chain = static_cast<TrackChain*>(object);
	chain->setScale(m_scale);
	bFetchNext = true;
}

//////////////////////////////////////////////////////////////////////////
// class TrackChainEditCMPT::TranslationVisitor
//////////////////////////////////////////////////////////////////////////

void TrackChainEditCMPT::TranslationVisitor::
visit(IObject* object, bool& bFetchNext)
{
	TrackChain* chain = static_cast<TrackChain*>(object);
	chain->setTranslation(m_offset);
	bFetchNext = true;
}