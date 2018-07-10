#include "SelectSpritesOP.h"

#include "Component/AbstractEditCMPT.h"
#include "View/PropertySettingPanel.h"
#include "View/SpritePropertySetting.h"
#include "View/MultiSpritesPropertySetting.h"
#include "View/MultiSpritesImpl.h"
#include "Render/DrawSelectedSpriteVisitor.h"

using namespace wxgui;

SelectSpritesOP::SelectSpritesOP(EditPanel* editPanel, MultiSpritesImpl* spritesImpl, 
								 PropertySettingPanel* propertyPanel, AbstractEditCMPT* callback/* = NULL*/,
								 const f2Colorf& color /*= f2Colorf(0, 0, 0)*/)
	: DrawRectangleOP(editPanel, color)
	, m_callback(callback)
	, m_spritesImpl(spritesImpl)
	, m_propertyPanel(propertyPanel)
{
	m_selection = spritesImpl->getSpriteSelection();
	m_selection->retain();

	m_firstPos.setInvalid();
}

SelectSpritesOP::~SelectSpritesOP()
{
	m_selection->clear();
	m_selection->release();
}

bool SelectSpritesOP::onKeyDown(int keyCode)
{
	if (DrawRectangleOP::onKeyDown(keyCode)) return true;

	if (keyCode == WXK_DELETE)
		m_spritesImpl->removeSpriteSelection();	

	return false;
}

bool SelectSpritesOP::onMouseLeftDown(int x, int y)
{
	f2Vec2 pos = m_editPanel->transPosScreenToProject(x, y);
	ISprite* selected = m_spritesImpl->querySpriteByPos(pos);
	if (selected)
	{
		if (wxGetKeyState(WXK_CONTROL))
		{
			if (m_selection->isExist(selected))
				m_selection->erase(selected);
			else
			{
				m_selection->insert(selected);
				if (m_propertyPanel)
				{
					if (m_selection->size() == 1)
						m_propertyPanel->setPropertySetting(createPropertySetting(selected));
					else
						m_propertyPanel->setPropertySetting(NULL);
				}
			}
		}
		else
		{
			if (!m_selection->isExist(selected))
			{
				m_selection->clear();
				m_selection->insert(selected);
				if (m_propertyPanel)
					m_propertyPanel->setPropertySetting(createPropertySetting(selected));
			}
		}
		m_firstPos.setInvalid();

		if (m_callback)
			m_callback->updateControlValue();
	}
	else
	{
		DrawRectangleOP::onMouseLeftDown(x, y);
		m_firstPos = pos;
		m_selection->clear();
		m_editPanel->Refresh();
	}

	return false;
}

bool SelectSpritesOP::onMouseLeftUp(int x, int y)
{
	if (DrawRectangleOP::onMouseLeftUp(x, y)) return true;

	if (m_firstPos.isValid())
	{
		f2AABB aabb(m_firstPos, m_editPanel->transPosScreenToProject(x, y));
		std::vector<ISprite*> sprites;
		m_spritesImpl->querySpritesByAABB(aabb, sprites);
		for (size_t i = 0, n = sprites.size(); i < n; ++i)
			m_selection->insert(sprites[i]);

		if (m_propertyPanel)
		{
			if (m_selection->size() == 1)
				m_propertyPanel->setPropertySetting(createPropertySetting(sprites[0]));
			else if (m_selection->size() > 1)
				m_propertyPanel->setPropertySetting(createPropertySetting(sprites));
			else
				m_propertyPanel->setPropertySetting(NULL);
		}

		m_firstPos.setInvalid();

		if (m_callback)
			m_callback->updateControlValue();
	}

	return false;
}

bool SelectSpritesOP::onDraw() const
{
	if (DrawRectangleOP::onDraw()) return true;

	m_selection->traverse(DrawSelectedSpriteVisitor(f2Colorf(1, 0, 0)));

	return false;
}

bool SelectSpritesOP::clear()
{
	if (DrawRectangleOP::clear()) return true;

	m_selection->clear();
	m_firstPos.setInvalid();

	return false;
}

IPropertySetting* SelectSpritesOP::createPropertySetting(wxgui::ISprite* sprite) const
{
	return new SpritePropertySetting(m_editPanel, sprite);
}

IPropertySetting* SelectSpritesOP::createPropertySetting(const std::vector<ISprite*>& sprites) const
{
	return new MultiSpritesPropertySetting(m_editPanel, sprites);
}
