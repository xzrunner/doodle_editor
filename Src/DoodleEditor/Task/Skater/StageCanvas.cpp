#include "StageCanvas.h"
#include "StagePanel.h"
#include "Frame/defs.h"

using namespace deditor::skater;

StageCanvas::StageCanvas(StagePanel* parent)
	: wxgui::GLCanvas(parent)
{
}

void StageCanvas::onDraw()
{
	drawGuideLines();

	StagePanel* editPanel = static_cast<StagePanel*>(m_editPanel);
	editPanel->traverseSprites(DrawSpriteVisitor(), wxgui::e_visible);
	editPanel->traverseShapes(DrawChainVisitor(), wxgui::e_visible);
	editPanel->drawEditTemp();
}

void StageCanvas::drawGuideLines()
{
	const int GRID_SIZE = 100;

	glColor3f(LIGHT_GRAY.r, LIGHT_GRAY.g, LIGHT_GRAY.b);

	glPushMatrix();
	glBegin(GL_LINES);
		glVertex2f(0.0f, 0.0f);
		glVertex2f(SCREEN_WIDTH * GRID_SIZE, 0.0f);
		glVertex2f(SCREEN_WIDTH * GRID_SIZE, SCREEN_HEIGHT);
		glVertex2f(0.0f, SCREEN_HEIGHT);
		for (size_t i = 0; i <= GRID_SIZE; ++i)
		{
			glVertex2f(SCREEN_WIDTH * i, 0.0f);
			glVertex2f(SCREEN_WIDTH * i, SCREEN_HEIGHT);
		}
	glEnd();
	glPopMatrix();
}

//////////////////////////////////////////////////////////////////////////
// class StageCanvas::DrawSpriteVisitor
//////////////////////////////////////////////////////////////////////////

StageCanvas::DrawSpriteVisitor::DrawSpriteVisitor()
{
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
}

void StageCanvas::DrawSpriteVisitor::visit(IObject* object, bool& bFetchNext)
{
	bFetchNext = true;

	wxgui::ISprite* sprite = static_cast<wxgui::ISprite*>(object);
	wxgui::ImageSprite* imageSprite = dynamic_cast<wxgui::ImageSprite*>(sprite);
	if (!imageSprite) return;

	glPushMatrix();
	glTranslatef(sprite->getPosition().x, sprite->getPosition().y, 1.0f);
	glRotatef(sprite->getAngle() * TRANS_RAD_TO_DEG, 0, 0, 1);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

	const float width = sprite->getSymbol().getWidth(),
		height = sprite->getSymbol().getHeight();

	f2Vec2 srcMin, srcMax, dstMin, dstMax;

	float* userData = static_cast<float*>(sprite->getUserData());
	srcMin.x = userData[0];
	srcMin.y = userData[1];
	srcMax.x = userData[2];
	srcMax.y = userData[3];

	dstMin.x = width * (userData[0] - 0.5f);
	dstMin.y = height * (userData[1] - 0.5f);
	dstMax.x = width * (userData[2] - 0.5f);
	dstMax.y = height * (userData[3] - 0.5f);

	glBindTexture(GL_TEXTURE_2D, imageSprite->getSymbol().getTextureID());
	glBegin(GL_QUADS);
		glTexCoord2f(srcMin.x, srcMin.y); glVertex2f(dstMin.x, dstMin.y);
		glTexCoord2f(srcMax.x, srcMin.y); glVertex2f(dstMax.x, dstMin.y);
		glTexCoord2f(srcMax.x, srcMax.y); glVertex2f(dstMax.x, dstMax.y);
		glTexCoord2f(srcMin.x, srcMax.y); glVertex2f(dstMin.x, dstMax.y);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, NULL);

	glDisable(GL_BLEND);

	glPopMatrix();
}

//////////////////////////////////////////////////////////////////////////
// class StageCanvas::DrawChainVisitor
//////////////////////////////////////////////////////////////////////////

StageCanvas::DrawChainVisitor::DrawChainVisitor()
{
	glColor3f(0.0f, 0.0f, 0.0f);
	glLineWidth(2.0f);
	glPushMatrix();
}

StageCanvas::DrawChainVisitor::~DrawChainVisitor()
{
	glPopMatrix();
	glLineWidth(1.0f);
}

void StageCanvas::DrawChainVisitor::visit(IObject* object, bool& bFetchNext)
{
	wxgui::IShape* shape = static_cast<wxgui::IShape*>(object);
	shape->draw();
	bFetchNext = true;
}