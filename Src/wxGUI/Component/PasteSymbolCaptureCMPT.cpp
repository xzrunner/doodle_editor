#include "PasteSymbolCaptureCMPT.h"

#include "Edit/PasteSymbolCaptureOP.h"

#include <wx/spinctrl.h>

using namespace wxgui;

PasteSymbolCaptureCMPT::PasteSymbolCaptureCMPT(wxWindow* parent, const wxString& name,
											   EditPanel* editPanel, MultiSpritesImpl* spritesImpl, 
											   LibraryPanel* libraryPanel)
	: AbstractEditCMPT(parent, name, editPanel)
{
	m_editOP = new PasteSymbolCaptureOP(editPanel, spritesImpl, libraryPanel, this);
}

f2Vec2 PasteSymbolCaptureCMPT::getOffset() const
{
	return f2Vec2(m_xSpin->GetValue(), m_ySpin->GetValue());
}

wxSizer* PasteSymbolCaptureCMPT::initLayout()
{
	wxStaticBox* bounding = new wxStaticBox(this, wxID_ANY, wxT("自动偏移"));
	wxBoxSizer* sizer = new wxStaticBoxSizer(bounding, wxVERTICAL);

	wxBoxSizer* xSizer = new wxBoxSizer(wxHORIZONTAL);
	xSizer->Add(new wxStaticText(this, wxID_ANY, wxT("水平偏移: ")));
	m_xSpin = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS | wxALIGN_RIGHT, -200, 200, 0);
	xSizer->Add(m_xSpin);
	sizer->Add(xSizer);

	wxBoxSizer* ySizer = new wxBoxSizer(wxHORIZONTAL);
	ySizer->Add(new wxStaticText(this, wxID_ANY, wxT("竖直偏移: ")));
	m_ySpin = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS | wxALIGN_RIGHT, -200, 200, 0);
	ySizer->Add(m_ySpin);
	sizer->Add(ySizer);

	return sizer;
}