#include "SelectBodyOP.h"
#include "BodyPropertySetting.h"
#include "DrawUtils.h"
#include "StagePanel.h"

using namespace deditor::modeling;

SelectBodyOP::SelectBodyOP(wxgui::EditPanel* editPanel, 
						   wxgui::MultiSpritesImpl* spritesImpl, 
						   wxgui::PropertySettingPanel* propertyPanel, 
						   wxgui::AbstractEditCMPT* callback/* = NULL*/,
						   const f2Colorf& color /*= f2Colorf(1, 1, 1)*/)
	: wxgui::SelectSpritesOP(editPanel, spritesImpl, propertyPanel, callback, color)
	, m_mouseOn(NULL)
{
}

bool SelectBodyOP::onKeyDown(int keyCode)
{
	if (wxgui::SelectSpritesOP::onKeyDown(keyCode)) return true;

	if (keyCode == WXK_DELETE && m_mouseOn)
		m_mouseOn = NULL;

	return false;
}

bool SelectBodyOP::onMouseMove(int x, int y)
{
	if (wxgui::SelectSpritesOP::onMouseMove(x, y)) return true;

	m_mouseOn = NULL;

	f2Vec2 pos = m_editPanel->transPosScreenToProject(x, y);
	wxgui::ISprite* sprite = static_cast<StagePanel*>(m_editPanel)->querySpriteByPos(pos);
	if (sprite)
		m_mouseOn = static_cast<BodyData*>(sprite->getUserData());

	m_editPanel->Refresh();

	return false;
}

bool SelectBodyOP::onDraw() const
{
	if (wxgui::DrawRectangleOP::onDraw()) return true;

	m_selection->traverse(DrawSelectedVisitor());

	if (m_mouseOn)
		DrawUtils::drawBody(m_mouseOn, DrawUtils::e_mouseOn);

	return false;
}

bool SelectBodyOP::clear()
{
	if (wxgui::SelectSpritesOP::clear()) return true;

	m_mouseOn = NULL;

	return false;
}

wxgui::IPropertySetting* SelectBodyOP::createPropertySetting(wxgui::ISprite* sprite) const
{
	return new BodyPropertySetting(m_editPanel, sprite);
}

//////////////////////////////////////////////////////////////////////////
// class SelectBodyOP::DrawSelectedVisitor
//////////////////////////////////////////////////////////////////////////

void SelectBodyOP::DrawSelectedVisitor::
visit(IObject* object, bool& bFetchNext) 
{
	std::vector<f2Vec2> bound;
	wxgui::ISprite* sprite = static_cast<wxgui::ISprite*>(object);
	BodyData* body = static_cast<BodyData*>(sprite->getUserData());
	DrawUtils::drawBody(body, DrawUtils::e_selected);
	bFetchNext = true;
}