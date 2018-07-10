#include "PasteSpriteCMPT.h"

#include "Edit/PasteSpriteOP.h"

using namespace wxgui;

PasteSpriteCMPT::PasteSpriteCMPT(wxWindow* parent, const wxString& name, 
								 EditPanel* editPanel, SpritesPanelImpl* spritesImpl,
								 PropertySettingPanel* propertyPanel)
	: AbstractEditCMPT(parent, name, editPanel)
{
	m_editOP = new PasteSpriteOP(editPanel, spritesImpl, propertyPanel, this);
}

wxSizer* PasteSpriteCMPT::initLayout()
{
	wxStaticBox* bounding = new wxStaticBox(this, wxID_ANY, wxT("����"));
	wxBoxSizer* sizer = new wxStaticBoxSizer(bounding, wxVERTICAL);

// 	wxBoxSizer* xSizer = new wxBoxSizer(wxHORIZONTAL);
// 	xSizer->Add(new wxStaticText(this, wxID_ANY, wxT("ˮƽƫ��: ")));
//	wxCheckBox* m_xCheckBox = new wxCheckBox(this, wxID_ANY, wxT("ˮƽ����"));

	sizer->Add(m_xMirror = new wxCheckBox(this, wxID_ANY, wxT("ˮƽ����")));
	sizer->AddSpacer(10);
	sizer->Add(m_yMirror = new wxCheckBox(this, wxID_ANY, wxT("��ֱ����")));

	return sizer;
}