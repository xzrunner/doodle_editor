#include "StageCanvas.h"
#include "StagePanel.h"
#include "Actor.h"
#include "Blackboard.h"
#include "IObstacleData.h"

#include "Frame/defs.h"

using namespace deditor::motox;

StageCanvas::StageCanvas(StagePanel* editPanel)
	: GLCanvas(editPanel)
	, m_editPanel(editPanel)
	, m_batch(500, wxgui::SpriteBatch::USAGE_STATIC)
{
}

StageCanvas::~StageCanvas()
{
	for (size_t i = 0, n = m_polys.size(); i < n; ++i)
		m_polys[i]->release();
	m_polys.clear();
}

void StageCanvas::clear()
{
	for (size_t i = 0, n = m_polys.size(); i < n; ++i)
		m_polys[i]->release();
	m_polys.clear();
}

void StageCanvas::onDraw()
{
	if (Blackboard::isCameraFocusOnMotobike)
		m_camera->setCenter(m_editPanel->getActor()->getCenterPos());

	drawGuideLines();
	drawPolygonFillings();
	
	switch (wxgui::Settings::drawType)
	{
	case wxgui::Settings::e_DrawBoth:
		m_editPanel->traverseShapes(wxgui::DrawShapesVisitor(), wxgui::e_visible);
		{
			std::vector<wxgui::ISprite*> sprites;
			m_editPanel->traverseSprites(FetchAllVisitor<wxgui::ISprite>(sprites),
				wxgui::e_visible);
			drawSprites(sprites);
		}
		if (m_editPanel->m_actor) 
			m_editPanel->m_actor->onDraw();
		m_editPanel->drawPhysics();
		break;
	case wxgui::Settings::e_DrawImage:
		m_editPanel->traverseShapes(wxgui::DrawShapesVisitor(), wxgui::e_visible);
		{
			std::vector<wxgui::ISprite*> sprites;
			m_editPanel->traverseSprites(FetchAllVisitor<wxgui::ISprite>(sprites),
				wxgui::e_visible);
			drawSprites(sprites);
		}
		if (m_editPanel->m_actor) 
			m_editPanel->m_actor->onDraw();
		break;
	case wxgui::Settings::e_DrawPhysics:
		m_editPanel->drawPhysics();
		break;
	}

	m_editPanel->drawEditTemp();
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

void StageCanvas::drawPolygonFillings()
{
	for (size_t i = 0, n = m_polys.size(); i < n; ++i)
		m_polys[i]->draw();
}

void StageCanvas::drawSprites(const std::vector<wxgui::ISprite*>& sprites)
{
	std::vector<wxgui::ISprite*> commonSprites;
	std::vector<wxgui::ISprite*> obstacleSprites;

	for (size_t i = 0, n = sprites.size(); i < n; ++i)
	{
		if (!sprites[i]->getUserData())
			commonSprites.push_back(sprites[i]);
		else
			obstacleSprites.push_back(sprites[i]);
	}

	wxgui::SpriteDraw::drawSprites(commonSprites, m_batch);

	for (size_t i = 0, n = obstacleSprites.size(); i < n; ++i)
		drawObstacleSprite(obstacleSprites[i]);
}

void StageCanvas::drawObstacleSprite(wxgui::ISprite* sprite)
{
	wxgui::ImageSprite* imageSprite = dynamic_cast<wxgui::ImageSprite*>(sprite);
	if (!imageSprite) return;

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

	glBindTexture(GL_TEXTURE_2D, imageSprite->getSymbol().getTextureID());

	IObstacleData* obstacle = static_cast<IObstacleData*>(sprite->getUserData());
	std::vector<f2Vec2> vertices;
	std::vector<f2Vec2> texCoords;
	obstacle->assemblyVertexArray(vertices, texCoords);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glVertexPointer(2, GL_FLOAT, 0, &vertices[0]);
	glTexCoordPointer(2, GL_FLOAT, 0, &texCoords[0]);

	glDrawArrays(GL_TRIANGLES, 0, (GLsizei)vertices.size());

	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);

	glDisable(GL_BLEND);
}