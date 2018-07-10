	#include "ArrangeSpriteOP.h"
#include "StagePanel.h"

using namespace deditor::automatic_merge;

ArrangeSpriteOP::ArrangeSpriteOP(StagePanel* editPanel, 
								 wxgui::PropertySettingPanel* propertyPanel,
								 wxgui::AbstractEditCMPT* callback/* = NULL*/)
	: wxgui::ArrangeSpriteOP<wxgui::SelectSpritesOP>(editPanel, editPanel, propertyPanel, callback)
{
	m_editPanel = editPanel;
}

bool ArrangeSpriteOP::onMouseLeftUp(int x, int y)
{
	if (wxgui::ArrangeSpriteOP<wxgui::SelectSpritesOP>::onMouseLeftUp(x, y)) return true;

	m_selection->traverse(FixCoordsVisitor());

	return false;
}

bool ArrangeSpriteOP::onMouseRightDown(int x, int y)
{
	if (wxgui::ArrangeSpriteOP<wxgui::SelectSpritesOP>::onMouseRightDown(x, y)) return true;

	onMouseLeftDown(x, y);

	return false;
}

bool ArrangeSpriteOP::onMouseRightUp(int x, int y)
{
	return onMouseLeftUp(x, y);
}

bool ArrangeSpriteOP::onDraw() const
{
	m_editPanel->traverseSprites(
		wxgui::DrawSelectedSpriteVisitor(f2Colorf(1.0f, 1.0f, 0.0f)),
		wxgui::e_visible
		);
	return wxgui::ArrangeSpriteOP<wxgui::SelectSpritesOP>::onDraw();
}

//////////////////////////////////////////////////////////////////////////
// class ArrangeSpriteOP::FixCoordsVisitor
//////////////////////////////////////////////////////////////////////////

void ArrangeSpriteOP::FixCoordsVisitor::
visit(IObject* object, bool& bFetchNext)
{
	wxgui::ISprite* sprite = static_cast<wxgui::ISprite*>(object);

	const f2Vec2& pos = sprite->getPosition();

	const float width = sprite->getSymbol().getWidth(),
		height = sprite->getSymbol().getHeight();

	f2Vec2 leftTop;
	leftTop.x = pos.x - width * 0.5f;
	leftTop.y = pos.y - height * 0.5f;

	if (leftTop.x == std::floor(leftTop.x) && 
		leftTop.y == std::floor(leftTop.y))
		return;

	f2Vec2 fixedCenter;
	fixedCenter.x = leftTop.x > 0 ? leftTop.x + 0.5f : leftTop.x - 0.5f;
	fixedCenter.y = leftTop.y > 0 ? leftTop.y + 0.5f : leftTop.y - 0.5f;
	fixedCenter.x = int(fixedCenter.x) + width * 0.5f;
	fixedCenter.y = int(fixedCenter.y) + height * 0.5f;

	sprite->setTransform(fixedCenter, sprite->getAngle());
	bFetchNext = true;
}