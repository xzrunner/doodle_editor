#include "StagePanel.h"
#include "StageCanvas.h"
#include "Blackboard.h"

using namespace deditor::magic_defence;

StagePanel::StagePanel(wxWindow* parent, wxgui::LibraryPanel* libraryPanel)
	: EditPanel(parent)
	, SpritesPanelImpl(this, libraryPanel)
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
	if (pos.x < 0 || pos.x > Blackboard::edge * Blackboard::length ||
		pos.y < 0 || pos.y > Blackboard::edge * Blackboard::row)
	{
		fixed.setInvalid();
	}
	else
	{
		const int row = (int) ((pos.y - 0.0f) / Blackboard::edge);
		fixed.x = pos.x;
		fixed.y = Blackboard::edge * (row + 0.5f);
	}

	return fixed;
}