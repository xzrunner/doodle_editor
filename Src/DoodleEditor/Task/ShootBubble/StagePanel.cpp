#include "StagePanel.h"
#include "StageCanvas.h"
#include "Blackboard.h"

using namespace deditor::shoot_bubble;

StagePanel::StagePanel(wxWindow* parent, wxgui::LibraryPanel* libraryPanel)
	: EditPanel(parent)
	, SpritesPanelImpl(this, libraryPanel)
{
	m_canvas = new StageCanvas(this);
}

void StagePanel::insertSprite(wxgui::ISprite* sprite)
{
	sprite->setTransform(fixSpriteLocation(sprite->getPosition()), 0);
	if (sprite->getPosition().isValid())
		wxgui::SpritesPanelImpl::insertSprite(sprite);
}

void StagePanel::clear()
{
	EditPanel::clear();
	SpritesPanelImpl::clear();
}

void StagePanel::transCoordsToGridPos(const f2Vec2& pos, int& row, int& col) const
{
	float hEdge, posOffset, posOffset1, rowOffset;
	computeParams(hEdge, posOffset, posOffset1, rowOffset);

	row = (int) ((-pos.y - posOffset1) / rowOffset + 0.5f);
	assert(fabs(-posOffset1 - rowOffset * row - pos.y) < LARGE_EPSILON);

	if (row % 2)
	{
		col = (int) (pos.x / Blackboard::edge + 0.5) - 1;
		assert(fabs(Blackboard::edge * (col + 1) - pos.x) < LARGE_EPSILON);
	}
	else
	{
		col = (int) ((pos.x + hEdge) / Blackboard::edge + 0.5f) - 1;
		assert(fabs(hEdge + Blackboard::edge * col - pos.x) < LARGE_EPSILON);
	}
}

void StagePanel::transGridPosToCoords(int row, int col, f2Vec2& pos) const
{
	float hEdge, posOffset, posOffset1, rowOffset;
	computeParams(hEdge, posOffset, posOffset1, rowOffset);

	pos.y = -posOffset1 - rowOffset * row;
	if (row % 2)
		pos.x = (col + 1) * Blackboard::edge;
	else
		pos.x = hEdge + Blackboard::edge * col;
}

void StagePanel::computeParams(float& hEdge, float& posOffset, 
							   float& posOffset1, float& rowOffset) const
{
	hEdge = Blackboard::edge * 0.5f;
	posOffset = hEdge / 1.732051;
	posOffset1 = posOffset * 2;
	rowOffset = hEdge * 1.732051;
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

	float hEdge, posOffset, posOffset1, rowOffset;
	computeParams(hEdge, posOffset, posOffset1, rowOffset);

	int width = Blackboard::edge * Blackboard::col,
		height = posOffset1 + rowOffset * (Blackboard::row - 1) + posOffset1;
	if (pos.x < 0 || pos.x > width ||
		pos.y > 0 || pos.y < -height)
	{
		fixed.setInvalid();
	}
	else
	{
		fixed.x = hEdge + (int) (pos.x / Blackboard::edge) * Blackboard::edge;
		if (-pos.y < posOffset1)
		{
			fixed.y = -posOffset1;
		}
		else
		{
			int row = (int) ((-pos.y - posOffset1) / rowOffset);

			f2Vec2 c0, c1;
			c0.y = -posOffset1 - rowOffset * row;
			c1.y = -posOffset1 - rowOffset * (row + 1);
			if (row % 2)
			{
				c0.x = Blackboard::edge + (int)((pos.x - hEdge) / Blackboard::edge) * Blackboard::edge;
				c1.x = fixed.x;
			}
			else
			{
				c0.x = fixed.x;
				c1.x = Blackboard::edge + (int)((pos.x - hEdge) / Blackboard::edge) * Blackboard::edge;
			}

			if (f2Math::getDistanceSquare(pos, c0) < f2Math::getDistanceSquare(pos, c1))
				fixed = c0;
			else
				fixed = c1;
		}
	}

	return fixed;
}
