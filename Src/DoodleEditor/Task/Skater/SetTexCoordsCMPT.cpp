#include "SetTexCoordsCMPT.h"
#include "ArrangeSpriteOP.h"
#include "StagePanel.h"

using namespace deditor::skater;

SetTexCoordsCMPT::SetTexCoordsCMPT(wxWindow* parent, const wxString& name,
								   StagePanel* editPanel,
								   wxgui::PropertySettingPanel* propertyPanel)
	: wxgui::AbstractEditCMPT(parent, name, editPanel)
{
	m_editOP = new ArrangeSpriteOP(editPanel, propertyPanel, this);
}

void SetTexCoordsCMPT::updateControlValue()
{
	float* data = NULL;

	wxgui::SpriteSelection* selection = static_cast<StagePanel*>(m_editPanel)->getSpriteSelection();
	if (selection->size() == 0)
	{
		data = NULL;
	}
	else if (selection->size() == 1)
	{
		wxgui::ISprite* sprite;
		selection->traverse(FetchFirstSelectedVisitor(&sprite));
		assert(sprite);
		data = static_cast<float*>(sprite->getUserData());
	}
	else
	{
		float coords[4];
		coords[0] = coords[1] = 0;
		coords[2] = coords[3] = 1;
		data = coords;
	}

	if (data)
	{
		m_texCoordsCtrl.enable();
		m_texCoordsCtrl.setValue(data);
	}
	else
	{
		m_texCoordsCtrl.disable();
	}
}

wxSizer* SetTexCoordsCMPT::initLayout()
{
	wxStaticBox* bounding = new wxStaticBox(this, wxID_ANY, wxT("ÎÆÀí×ø±êÉèÖÃ"));
	wxBoxSizer* sizer = new wxStaticBoxSizer(bounding, wxVERTICAL);

	m_texCoordsCtrl.leftSlider = new wxSlider(this, wxID_ANY, 0, 0, 100);
	sizer->Add(m_texCoordsCtrl.leftSlider);

	wxBoxSizer* verticalSizer = new wxBoxSizer(wxHORIZONTAL);
	m_texCoordsCtrl.downSlider = new wxSlider(this, wxID_ANY, 0, 0, 100, wxDefaultPosition, wxDefaultSize, wxSL_VERTICAL | wxSL_INVERSE);
	verticalSizer->Add(m_texCoordsCtrl.downSlider);
	verticalSizer->AddSpacer(40);
	m_texCoordsCtrl.upSlider = new wxSlider(this, wxID_ANY, 100, 0, 100, wxDefaultPosition, wxDefaultSize, wxSL_VERTICAL | wxSL_INVERSE);
	verticalSizer->Add(m_texCoordsCtrl.upSlider);
	sizer->Add(verticalSizer);

	m_texCoordsCtrl.rightSlider = new wxSlider(this, wxID_ANY, 100, 0, 100);
	sizer->Add(m_texCoordsCtrl.rightSlider);

	Connect(m_texCoordsCtrl.leftSlider->GetId(), wxEVT_COMMAND_SLIDER_UPDATED, 
		wxScrollEventHandler(SetTexCoordsCMPT::onChangeTexCoords));
	Connect(m_texCoordsCtrl.rightSlider->GetId(), wxEVT_COMMAND_SLIDER_UPDATED, 
		wxScrollEventHandler(SetTexCoordsCMPT::onChangeTexCoords));
	Connect(m_texCoordsCtrl.downSlider->GetId(), wxEVT_COMMAND_SLIDER_UPDATED, 
		wxScrollEventHandler(SetTexCoordsCMPT::onChangeTexCoords));
	Connect(m_texCoordsCtrl.upSlider->GetId(), wxEVT_COMMAND_SLIDER_UPDATED, 
		wxScrollEventHandler(SetTexCoordsCMPT::onChangeTexCoords));

	return sizer;
}

void SetTexCoordsCMPT::onChangeTexCoords(wxScrollEvent& event)
{
	wxgui::SpriteSelection* selection = static_cast<StagePanel*>(m_editPanel)->getSpriteSelection();
	if (!selection->empty())
	{
		selection->traverse(SetTexCoordsVisitor(m_texCoordsCtrl));
		m_editPanel->Refresh();
	}
}

//////////////////////////////////////////////////////////////////////////
// struct SetTexCoordsCMPT::TexCoordsCtrl
//////////////////////////////////////////////////////////////////////////

void SetTexCoordsCMPT::TexCoordsCtrl::disable()
{
	leftSlider->Disable();
	rightSlider->Disable();
	downSlider->Disable();
	upSlider->Disable();
}

void SetTexCoordsCMPT::TexCoordsCtrl::enable()
{
	leftSlider->Enable();
	rightSlider->Enable();
	downSlider->Enable();
	upSlider->Enable();
}

void SetTexCoordsCMPT::TexCoordsCtrl::setValue(float* val)
{
	leftSlider->SetValue((int)(val[0] * 100));
	downSlider->SetValue((int)(val[1] * 100));
	rightSlider->SetValue((int)(val[2] * 100));
	upSlider->SetValue((int)(val[3] * 100));
}

//////////////////////////////////////////////////////////////////////////
// class SetTexCoordsCMPT::FetchFirstSelectedVisitor
//////////////////////////////////////////////////////////////////////////

SetTexCoordsCMPT::FetchFirstSelectedVisitor::FetchFirstSelectedVisitor(wxgui::ISprite** pFirst)
{
	m_pFirst = pFirst;
}

void SetTexCoordsCMPT::FetchFirstSelectedVisitor::visit(IObject* object, bool& bFetchNext)
{
	*m_pFirst = static_cast<wxgui::ISprite*>(object);
	bFetchNext = false;
}

//////////////////////////////////////////////////////////////////////////
// class SetTexCoordsCMPT::SetTexCoordsVisitor
//////////////////////////////////////////////////////////////////////////

SetTexCoordsCMPT::SetTexCoordsVisitor::SetTexCoordsVisitor(const TexCoordsCtrl& texCoordsCtrl)
{
	float x0 = texCoordsCtrl.leftSlider->GetValue() * 0.01f,
		x1 = texCoordsCtrl.rightSlider->GetValue() * 0.01f,
		y0 = texCoordsCtrl.downSlider->GetValue() * 0.01f,
		y1 = texCoordsCtrl.upSlider->GetValue() * 0.01f;

	m_coords[0] = x0;
	m_coords[2] = x0 > x1 ? x0 : x1;

	m_coords[1] = y0;
	m_coords[3] = y0 > y1 ? y0 : y1;
}

void SetTexCoordsCMPT::SetTexCoordsVisitor::visit(IObject* object, bool& bFetchNext)
{
	wxgui::ImageSprite* sprite = static_cast<wxgui::ImageSprite*>(object);

	float* userData = static_cast<float*>(sprite->getUserData());
	for (size_t i = 0; i < 4; ++i)
		userData[i] = m_coords[i];
	sprite->buildBounding(static_cast<float*>(sprite->getUserData()));

	bFetchNext = true;
}
