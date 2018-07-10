#include "SpriteStageCanvas.h"

#include "View/EditPanel.h"
#include "View/MultiSpritesImpl.h"
#include "Render/DrawSpritesVisitor.h"

using namespace wxgui;

SpriteStageCanvas::SpriteStageCanvas(EditPanel* editPanel, MultiSpritesImpl* spritesImpl)
	: GLCanvas(editPanel)
	, m_spritesImpl(spritesImpl)
	, m_batch(500, SpriteBatch::USAGE_STATIC)
{
}

void SpriteStageCanvas::onDraw()
{
	m_spritesImpl->traverseSprites(DrawSpritesVisitor(m_batch), e_visible);
	m_editPanel->drawEditTemp();
}