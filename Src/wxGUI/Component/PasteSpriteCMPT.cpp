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
	wxStaticBox* bounding = new wxStaticBox(this, wxID_ANY, wxT("工具"));
	wxBoxSizer* sizer = new wxStaticBoxSizer(bounding, wxVERTICAL);

// 	wxBoxSizer* xSizer = new wxBoxSizer(wxHORIZONTAL);
// 	xSizer->Add(new wxStaticText(this, wxID_ANY, wxT("水平偏移: ")));
//	wxCheckBox* m_xCheckBox = new wxCheckBox(this, wxID_ANY, wxT("水平镜像"));

	sizer->Add(m_xMirror = new wxCheckBox(this, wxID_ANY, wxT("水平镜像")));
	sizer->AddSpacer(10);
	sizer->Add(m_yMirror = new wxCheckBox(this, wxID_ANY, wxT("竖直镜像")));

	return sizer;
}