#include "StageCanvas.h"
#include "StagePanel.h"

using namespace deditor::compress_pictures;

StageCanvas::StageCanvas(wxgui::EditPanel* parent)
	: wxgui::GLCanvas(parent)
{
}

void StageCanvas::onDraw()
{
	StagePanel* editPanel = static_cast<StagePanel*>(m_parent);
	if (editPanel->m_symbol)
	{
		const f2Vec2 left(-editPanel->m_symbol->getWidth() * 0.5f - SPACING, 0.0f),
			right(editPanel->m_symbol->getWidth() * 0.5f + SPACING, 0.0f);

		wxgui::SpriteDraw::drawSprite(editPanel->m_symbol, left);
		if (editPanel->m_compressedSymbol)
			wxgui::SpriteDraw::drawSprite(editPanel->m_compressedSymbol, right);
	}
}