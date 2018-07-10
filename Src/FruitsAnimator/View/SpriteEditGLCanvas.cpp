#include "SpriteEditGLCanvas.h"
#include "Dataset/Symbol.h"
#include "Dataset/Sprite.h"
#include "Tools/Render.h"

using namespace FRUITS_ANIMATOR;

SpriteEditGLCanvas::SpriteEditGLCanvas(wxgui::EditPanel* parent, Sprite* sprite)
	: wxgui::GLCanvas(parent)
	, m_sprite(sprite)
{
}

void SpriteEditGLCanvas::initGL()
{
	wxgui::GLCanvas::initGL();
	m_sprite->reloadTexture();
}

void SpriteEditGLCanvas::onDraw()
{
	Render::drawSpriteCenter(m_sprite);
	m_editPanel->drawEditTemp();
}