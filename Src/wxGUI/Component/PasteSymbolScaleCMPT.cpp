#include "PasteSymbolScaleCMPT.h"

#include "Edit/PasteSymbolOP.h"
#include "View/MultiSpritesImpl.h"
#include "View/LibraryPanel.h"

#include <wx/spinctrl.h>

using namespace wxgui;

PasteSymbolScaleCMPT::PasteSymbolScaleCMPT(wxWindow* parent, const wxString& name, 
										   EditPanel* editPanel, MultiSpritesImpl* spritesImpl, 
										   LibraryPanel* libraryPanel)
	: AbstractEditCMPT(parent, name, editPanel)
	, m_scaleVal(1.0f)
{
	m_editOP = new PasteSymbolOP(editPanel, spritesImpl, libraryPanel, &m_scaleVal);
}

wxSizer* PasteSymbolScaleCMPT::initLayout()
{
	wxSizer* topSizer = new wxBoxSizer(wxVERTICAL);
	{
		wxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
		sizer->Add(new wxStaticText(this, wxID_ANY, wxT("����: ")));

		wxSpinCtrl* scaleCtrl = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(50, -1), 
			wxSP_ARROW_KEYS, 10, 100, 100);
		Connect(scaleCtrl->GetId(), wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler(PasteSymbolScaleCMPT::onChangeScale));
		sizer->Add(scaleCtrl);

		sizer->Add(new wxStaticText(this, wxID_ANY, wxT("%")));
		topSizer->Add(sizer);
	}
	return topSizer;
}

void PasteSymbolScaleCMPT::onChangeScale(wxSpinEvent& event)
{
	m_scaleVal = event.GetValue() * 0.01f;
}