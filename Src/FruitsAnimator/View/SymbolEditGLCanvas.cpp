#include "SymbolEditGLCanvas.h"
#include "Dataset/Symbol.h"
#include "Dataset/MorphingSprite.h"
#include "Tools/Render.h"

using namespace FRUITS_ANIMATOR;

SymbolEditGLCanvas::SymbolEditGLCanvas(wxgui::EditPanel* parent, Symbol* symbol)
	: wxgui::GLCanvas(parent)
	, m_symbol(symbol)
	, m_drawMode(DrawInPixels)
{
}

void SymbolEditGLCanvas::setDrawMode(e_DrawMode mode)
{
	m_drawMode = mode;
}

wxgui::RawPixels* SymbolEditGLCanvas::getRawPixels()
{
	return m_symbol->getRawPixels();
}

wxgui::RawPixels::PixelBuf& SymbolEditGLCanvas::getSelectedPixels()
{
	return m_selectedPixels;
}

SymbolEditGLCanvas::RenderSetting& SymbolEditGLCanvas::getRenderSetting()
{
	return m_renderSetting;
}

void SymbolEditGLCanvas::initGL()
{
	wxgui::GLCanvas::initGL();
	m_symbol->reloadTexture();
}

void SymbolEditGLCanvas::onDraw()
{
	switch (m_drawMode)
	{
	case DrawInTexture:
		{
			MorphingSprite sprite(m_symbol, f2Vec2(0, 0), false);
			wxgui::Render::drawSpriteCenter(&sprite);
		}
		break;
	case DrawInPixels:
		{
			glBindTexture(GL_TEXTURE_2D, NULL);
			if (m_renderSetting.drawOriginalSymbol)
				Render::drawRawPixels(*m_symbol->getRawPixels());
			if (m_renderSetting.drawOriginalSymbol)
				Render::drawRawPixelsSelectedFlag(*m_symbol->getRawPixels(), m_selectedPixels);	
			else
				Render::drawRawPixelsSelected(*m_symbol->getRawPixels(), m_selectedPixels);
			if (m_renderSetting.drawPixelBound)
				Render::drawRawPixelsBound(*m_symbol->getRawPixels());
		}
		break;
	}
	m_editPanel->drawEditTemp();
}