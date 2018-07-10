#include "ArrangeSpriteFixOP.h"

#include "View/MultiSpritesImpl.h"

using namespace wxgui;

ArrangeSpriteFixOP::ArrangeSpriteFixOP(EditPanel* editPanel, MultiSpritesImpl* spritesImpl,
									   PropertySettingPanel* propertyPanel, AbstractEditCMPT* callback/* = NULL*/)
	: ArrangeSpriteOP(editPanel, spritesImpl, propertyPanel, callback)
	, m_spritesImpl(spritesImpl)
{
}

bool ArrangeSpriteFixOP::onMouseLeftUp(int x, int y)
{
	if (ArrangeSpriteOP::onMouseLeftUp(x, y)) return true;

	std::vector<ISprite*> sprites;
	m_selection->traverse(FetchAllVisitor<ISprite>(sprites));
	fixSpritesLocation(sprites);

	return false;
}

bool ArrangeSpriteFixOP::onMouseRightDown(int x, int y)
{
	if (ArrangeSpriteOP::onMouseRightDown(x, y)) return true;

	onMouseLeftDown(x, y);

	return false;
}

bool ArrangeSpriteFixOP::onMouseRightUp(int x, int y)
{
	return onMouseLeftUp(x, y);
}

void ArrangeSpriteFixOP::fixSpritesLocation(const std::vector<ISprite*>& sprites)
{
	for (size_t i = 0, n = sprites.size(); i < n; ++i)
		sprites[i]->retain();

	for (size_t i = 0, n = sprites.size(); i < n; ++i)
		m_spritesImpl->removeSprite(sprites[i]);
	for (size_t i = 0, n = sprites.size(); i < n; ++i)
		m_spritesImpl->insertSprite(sprites[i]);

	for (size_t i = 0, n = sprites.size(); i < n; ++i)
		sprites[i]->release();
}