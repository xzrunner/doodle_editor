#include "StagePanel.h"
#include "StageCanvas.h"
#include "Blackboard.h"

using namespace deditor::monster;

StagePanel::StagePanel(wxWindow* parent, wxgui::LibraryPanel* libraryPanel)
	: wxgui::EditPanel(parent)
	, wxgui::SpritesPanelImpl(this, libraryPanel)
{
	m_canvas = new StageCanvas(this);
}

void StagePanel::insertSprite(wxgui::ISprite* sprite)
{
	sprite->setTransform(fixSpriteLocation(sprite->getPosition()), 0);
	if (!sprite->getPosition().isValid()) return;

	wxgui::SpritesPanelImpl::insertSprite(sprite);

	if (!sprite->getUserData())
	{
		float* data = new float[1];
		data[0] = -1;
		sprite->setUserData(data);
	}

// 	float* data = new float[3];
// 	data[2] = -1;
// 	if (sprite->getPosition().y < 0)
// 	{
// 		const int col = (int) ((sprite->getPosition().x - 0.0f) / Blackboard::edge),
// 			row = (int) ((0.0f - sprite->getPosition().y) / Blackboard::edge);
// 		data[0] = col + 1;
// 		data[1] = - (row + 1);
// 	}
// 	else
// 	{
// 		const int col = (int) ((sprite->getPosition().x - 0.0f) / Blackboard::edge);
// 		data[0] = col + 1;
// 		data[1] = sprite->getPosition().y / (Blackboard::edge * Blackboard::length);
// 	}
// 	sprite->setUserData(data);

	if (sprite->getPosition().y < 0)
		traverseSprites(RemoveOverlappedUnderground(this, sprite));
}

void StagePanel::clear()
{
	EditPanel::clear();
	SpritesPanelImpl::clear();
}

void StagePanel::updateAllSpritesLocation()
{
	std::vector<wxgui::ISprite*> sprites;
	traverseSprites(FetchAllVisitor<wxgui::ISprite>(sprites));
	for (size_t i = 0, n = sprites.size(); i < n; ++i)
		sprites[i]->setTransform(fixSpriteLocation(sprites[i]->getPosition()), 0);
}

f2Vec2 StagePanel::fixSpriteLocation(const f2Vec2& pos) const
{
	f2Vec2 fixed;
	if (pos.x < 0 || pos.x > Blackboard::edge * Blackboard::col ||
		pos.y < -Blackboard::edge * Blackboard::row || pos.y > Blackboard::edge * Blackboard::length)
	{
		fixed.setInvalid();
	}
	else
	{
		if (pos.y < 0)
		{
			const int col = (int) ((pos.x - 0.0f) / Blackboard::edge),
				row = (int) ((0.0f - pos.y) / Blackboard::edge);
			fixed.x = Blackboard::edge * (col + 0.5f);
			fixed.y = Blackboard::edge * (-row - 0.5f);
		}
		else
		{
			const int col = (int) ((pos.x - 0.0f) / Blackboard::edge);
			fixed.x = Blackboard::edge * (col + 0.5f);
			fixed.y = pos.y;
		}
	}
	return fixed;
}

//////////////////////////////////////////////////////////////////////////
// class StagePanel::RemoveOverlappedUnderground
//////////////////////////////////////////////////////////////////////////

StagePanel::RemoveOverlappedUnderground::
RemoveOverlappedUnderground(wxgui::MultiSpritesImpl* spritesImpl, wxgui::ISprite* sprite)
	: m_spritesImpl(spritesImpl)
	, m_sprite(sprite)
{
}

void StagePanel::RemoveOverlappedUnderground::
visit(IObject* object, bool& bFetchNext)
{
	wxgui::ISprite* sprite = static_cast<wxgui::ISprite*>(object);
	if (sprite != m_sprite)
	{
		if (f2Math::getDistanceSquare(sprite->getPosition(), m_sprite->getPosition()) < LARGE_EPSILON)
		{
			m_spritesImpl->removeSprite(sprite);
			bFetchNext = false;
			return;
		}
	}
	bFetchNext = true;
}