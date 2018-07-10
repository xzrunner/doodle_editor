#include "SelectFixtureOP.h"
#include "StagePanel.h"
#include "BodyData.h"
#include "FixtureData.h"
#include "FixturePropertySetting.h"
#include "DrawUtils.h"

using namespace deditor::modeling;

SelectFixtureOP::SelectFixtureOP(StagePanel* editPanel, wxgui::PropertySettingPanel* propertyPanel)
	: wxgui::DrawRectangleOP(editPanel, f2Colorf(1, 1, 1))
	, m_selected(NULL)
	, m_mouseOn(NULL)
	, m_stagePanel(editPanel)
	, m_propertyPanel(propertyPanel)
{
	m_firstPos.setInvalid();
}

SelectFixtureOP::~SelectFixtureOP()
{
	
}

bool SelectFixtureOP::onMouseLeftDown(int x, int y)
{
	f2Vec2 pos = m_editPanel->transPosScreenToProject(x, y);
	wxgui::ISprite* sprite = m_stagePanel->querySpriteByPos(pos);
	if (!sprite) return false;

	m_selected = NULL;
	BodyData* body = static_cast<BodyData*>(sprite->getUserData());
	for (size_t i = 0, n = body->m_fixtures.size(); i < n; ++i)
	{
		if (body->m_fixtures[i]->isContain(pos))
		{
			m_selected = body->m_fixtures[i];
			break;
		}
	}
	if (m_selected)
	{
		wxgui::IPropertySetting* setting = new FixturePropertySetting(m_editPanel, m_selected);
		m_propertyPanel->setPropertySetting(setting);
	}
	else
	{
		wxgui::DrawRectangleOP::onMouseLeftDown(x, y);
		m_firstPos = pos;
		m_editPanel->Refresh();
	}

	return false;
}

bool SelectFixtureOP::onMouseLeftUp(int x, int y)
{
	if (wxgui::DrawRectangleOP::onMouseLeftUp(x, y)) return true;

	if (m_firstPos.isValid())
	{
		f2AABB aabb(m_firstPos, m_editPanel->transPosScreenToProject(x, y));
		std::vector<wxgui::ISprite*> sprites;
		m_stagePanel->querySpritesByAABB(aabb, sprites);

		m_selected = NULL;
		for (size_t i = 0, n = sprites.size(); i < n; ++i)
		{
			BodyData* body = static_cast<BodyData*>(sprites[i]->getUserData());
			for (size_t j = 0, m = body->m_fixtures.size(); j < m; ++j)
			{
				if (body->m_fixtures[j]->isIntersect(aabb))
				{
					m_selected = body->m_fixtures[i];
					break;
				}
			}
		}

		if (m_selected)
		{
			wxgui::IPropertySetting* setting = new FixturePropertySetting(m_editPanel, m_selected);
			m_propertyPanel->setPropertySetting(setting);
		}
		else
		{
			m_propertyPanel->setPropertySetting(NULL);
		}

		m_firstPos.setInvalid();
	}

	return false;
}

bool SelectFixtureOP::onMouseMove(int x, int y)
{
	if (wxgui::DrawRectangleOP::onMouseMove(x, y)) return true;

	m_mouseOn = NULL;

	f2Vec2 pos = m_editPanel->transPosScreenToProject(x, y);
	wxgui::ISprite* sprite = static_cast<StagePanel*>(m_editPanel)->querySpriteByPos(pos);
	if (sprite)
	{
		BodyData* body = static_cast<BodyData*>(sprite->getUserData());
		if (body)
		{
			for (size_t i = 0, n = body->m_fixtures.size(); i < n; ++i)
			{
				if (body->m_fixtures[i]->isContain(pos))
				{
					m_mouseOn = body->m_fixtures[i];
					break;
				}
			}
		}
	}

	m_editPanel->Refresh();

	return false;
}

bool SelectFixtureOP::onDraw() const
{
	if (wxgui::DrawRectangleOP::onDraw()) return true;

	if (m_selected)
		DrawUtils::drawFixture(m_selected, DrawUtils::e_selected, true);
	if (m_mouseOn)
		DrawUtils::drawFixture(m_mouseOn, DrawUtils::e_mouseOn, true);

	return false;
}

bool SelectFixtureOP::clear()
{
	if (wxgui::DrawRectangleOP::clear()) return true;

	m_firstPos.setInvalid();

	m_selected = m_mouseOn = NULL;

	return false;
}