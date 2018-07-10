#include "StageCanvas.h"
#include "StagePanel.h"
#include "TrackSurfaceData.h"

#include "Frame/defs.h"

using namespace deditor::hill_climb;

StageCanvas::StageCanvas(StagePanel* parent)
	: wxgui::ShapeStageCanvas(parent, parent)
	, m_batch(100, wxgui::SpriteBatch::USAGE_STATIC)
{
}

void StageCanvas::onDraw()
{
	StagePanel* stagePanel = static_cast<StagePanel*>(m_editPanel);

	drawGuideLines();
	stagePanel->traverseShapes(wxgui::DrawShapesVisitor(m_color), wxgui::e_visible);
	drawSurfaces();
	stagePanel->traverseSprites(wxgui::DrawSpritesVisitor(m_batch), wxgui::e_visible);
	stagePanel->drawEditTemp();
}

void StageCanvas::drawGuideLines()
{
	glColor3f(LIGHT_GRAY.r, LIGHT_GRAY.g, LIGHT_GRAY.b);

	glPushMatrix();

	glBegin(GL_LINE_LOOP);
		glVertex2f(0.0f, 0.0f);
		glVertex2f(SCREEN_WIDTH * GUIDE_LINES_WIDTH_TIMES, 0.0f);
		glVertex2f(SCREEN_WIDTH * GUIDE_LINES_WIDTH_TIMES, SCREEN_HEIGHT);
		glVertex2f(0.0f, SCREEN_HEIGHT);
	glEnd();

	glBegin(GL_LINES);
	float base = SCREEN_WIDTH;
	for (size_t i = 0; i < GUIDE_LINES_WIDTH_TIMES - 1; ++i)
	{
		glVertex2f(base, 0.0f);
		if ((i + 1) % 50 == 0)
			glVertex2f(base, SCREEN_HEIGHT * 2.0f);
		else if ((i + 1) % 5 == 0)
			glVertex2f(base, SCREEN_HEIGHT * 1.5f);
		else
			glVertex2f(base, SCREEN_HEIGHT);
		base += SCREEN_WIDTH;
	}
	glEnd();

	glPopMatrix();
}

void StageCanvas::drawSurfaces()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

	std::vector<wxgui::ChainShape*> trackChains;
	static_cast<StagePanel*>(m_editPanel)->traverseShapes(FetchAllVisitor<wxgui::ChainShape>(trackChains));
	for (size_t i = 0, n = trackChains.size(); i < n; ++i)
	{
		wxgui::ChainShape* chain = trackChains[i];

		if (!chain->getUserData()) continue;

		TrackSurfaceData* data = static_cast<TrackSurfaceData*>(chain->getUserData());

		glBindTexture(GL_TEXTURE_2D, data->image->textureID());

		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);

		glVertexPointer(2, GL_FLOAT, 0, &data->vertices[0]);
		glTexCoordPointer(2, GL_FLOAT, 0, &data->texCoords[0]);

		glDrawArrays(GL_TRIANGLE_STRIP, 0, (GLsizei)data->vertices.size());

		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);

		glBindTexture(GL_TEXTURE_2D, NULL);
	}

	glDisable(GL_BLEND);
}