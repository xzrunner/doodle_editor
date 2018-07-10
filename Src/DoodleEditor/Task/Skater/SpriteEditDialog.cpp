#include "SpriteEditDialog.h"
#include "SpriteEditCanvas.h"
#include "SetTextureCoordsOP.h"

using namespace deditor::skater;

SpriteEditDialog::SpriteEditDialog(wxWindow* parent, 
								   wxgui::ImageSprite* sprite)
	: wxDialog(parent, wxID_ANY, "Edit ISprite", wxDefaultPosition, wxSize(800, 600), wxCLOSE_BOX | wxCAPTION | wxMAXIMIZE_BOX)
{
	m_sprite = sprite;

	wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
	m_editPanel = new wxgui::EditPanel(this);
	m_editPanel->setEditOP(new SetTextureCoordsOP(m_editPanel, sprite));
	m_editPanel->setCanvas(new SpriteEditCanvas(m_editPanel, sprite));
	sizer->Add(m_editPanel, 1, wxEXPAND);
	SetSizer(sizer);
}

SpriteEditDialog::~SpriteEditDialog()
{
	delete m_editPanel;
}