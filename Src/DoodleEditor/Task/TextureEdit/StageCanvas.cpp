#include "StageCanvas.h"
#include "StagePanel.h"

using namespace deditor::texture_edit;

StageCanvas::StageCanvas(StagePanel* editPanel)
	: wxgui::GLCanvas(editPanel)
	, m_batch(100, wxgui::SpriteBatch::USAGE_STATIC)
{
}

void StageCanvas::onDraw()
{
	StagePanel* editPanel = static_cast<StagePanel*>(m_editPanel);

	wxgui::Image* image = editPanel->getTexture();
	if (image) image->draw();

	editPanel->traverseShapes(wxgui::DrawShapesVisitor(), wxgui::e_visible);
	editPanel->traverseSprites(wxgui::DrawSpritesVisitor(m_batch), wxgui::e_visible);
	editPanel->drawEditTemp();
}