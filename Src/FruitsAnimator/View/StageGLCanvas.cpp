#include "StageGLCanvas.h"
#include "StagePanel.h"
#include "Dataset/Sprite.h"
#include "Tools/Render.h"

using namespace FRUITS_ANIMATOR;

StageGLCanvas::StageGLCanvas(StagePanel* editPanel)
	: wxgui::GLCanvas(editPanel)
{
}

void StageGLCanvas::onDraw()
{
	drawbackground();
	static_cast<StagePanel*>(m_editPanel)->traverseSprites(DrawVisitor(), 
		wxgui::e_visible);
	m_editPanel->drawEditTemp();
}

void StageGLCanvas::drawbackground() const
{
	const float hWidth = GetSize().GetWidth() * 0.5f,
		hHeight = GetSize().GetHeight() * 0.5f;

 	glColor3f(0.0f, 0.0f, 0.0f);
 	glBegin(GL_LINES);
		glVertex2f(-hWidth, 0.0f);	glVertex2f(hWidth, 0.0f);
		glVertex2f(0.0f, -hHeight);	glVertex2f(0.0f, hHeight);
 	glEnd();
}

//////////////////////////////////////////////////////////////////////////
// class StageGLCanvas::DrawVisitor
//////////////////////////////////////////////////////////////////////////

StageGLCanvas::DrawVisitor::DrawVisitor()
{
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
}

void StageGLCanvas::DrawVisitor::visit(IObject* object, bool& bFetchNext)
{
	f2Sprite* sprite = static_cast<f2Sprite*>(object);

	const f2Vec2& pos = sprite->getPosition();

	glPushMatrix();
	glTranslatef(pos.x, pos.y, 1.0f);
	glRotatef(sprite->getAngle() * TRANS_RAD_TO_DEG, 0, 0, 1);

	Render::drawSpriteCenter(static_cast<Sprite*>(sprite));

	glPopMatrix();

	bFetchNext = true;
}