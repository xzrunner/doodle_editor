#include "SpriteEditCanvas.h"

using namespace deditor::skater;

SpriteEditCanvas::SpriteEditCanvas(wxgui::EditPanel* parent, 
								   wxgui::ISprite* sprite)
	: wxgui::GLCanvas(parent)
	, m_sprite(sprite)
{
}

void SpriteEditCanvas::initGL()
{
	wxgui::GLCanvas::initGL();
	m_sprite->getSymbol().reloadTexture();
}

void SpriteEditCanvas::onDraw()
{
	m_sprite->getSymbol().draw();
	m_editPanel->drawEditTemp();
}