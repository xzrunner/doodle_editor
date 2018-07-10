#include "ArrangeSpriteCMPT.h"
#include "StagePanel.h"

using namespace deditor::combination;

ArrangeSpriteCMPT::ArrangeSpriteCMPT(wxWindow* parent, const wxString& name, 
									 StagePanel* editPanel, wxgui::PropertySettingPanel* propertyPanel)
	: wxgui::AbstractEditCMPT(parent, name, editPanel)
{
	m_editOP = new wxgui::ArrangeSpriteOP<wxgui::SelectSpritesOP>(editPanel, editPanel, propertyPanel);
}

wxSizer* ArrangeSpriteCMPT::initLayout()
{
	wxBoxSizer* topSizer = new wxBoxSizer(wxVERTICAL);
	{
		wxButton* btn = new wxButton(this, wxID_ANY, wxT("水平翻转"));
		Connect(btn->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, 
			wxCommandEventHandler(ArrangeSpriteCMPT::onHorizontalFlip));
		topSizer->Add(btn);
	}
	topSizer->AddSpacer(10);
	{
		wxButton* btn = new wxButton(this, wxID_ANY, wxT("垂直翻转"));
		Connect(btn->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, 
			wxCommandEventHandler(ArrangeSpriteCMPT::onVerticalFlip));
		topSizer->Add(btn);
	}
	return topSizer;
}

void ArrangeSpriteCMPT::onHorizontalFlip(wxCommandEvent& event)
{
	std::vector<wxgui::ISprite*> sprites;
	static_cast<StagePanel*>(m_editPanel)->traverseSprites(FetchAllVisitor<wxgui::ISprite>(sprites));
	for (size_t i = 0, n = sprites.size(); i < n; ++i)
	{
		wxgui::ISprite* sprite = sprites[i];
		bool xMirror, yMirror;
		sprite->getMirror(xMirror, yMirror);
		sprite->translate(f2Vec2(-sprite->getPosition().x * 2.0f, 0.0f));
		sprite->setMirror(!xMirror, yMirror);
	}
	m_editPanel->Refresh();
}

void ArrangeSpriteCMPT::onVerticalFlip(wxCommandEvent& event)
{
	std::vector<wxgui::ISprite*> sprites;
	static_cast<StagePanel*>(m_editPanel)->traverseSprites(FetchAllVisitor<wxgui::ISprite>(sprites));
	for (size_t i = 0, n = sprites.size(); i < n; ++i)
	{
		wxgui::ISprite* sprite = sprites[i];
		bool xMirror, yMirror;
		sprite->getMirror(xMirror, yMirror);
		sprite->translate(f2Vec2(0.0f, -sprite->getPosition().y * 2.0f));
		sprite->setMirror(xMirror, !yMirror);
	}
	m_editPanel->Refresh();
}
