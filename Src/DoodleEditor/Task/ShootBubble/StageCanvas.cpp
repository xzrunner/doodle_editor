#include "StageCanvas.h"
#include "StagePanel.h"
#include "Blackboard.h"

#include "Frame/defs.h"

using namespace deditor::shoot_bubble;

StageCanvas::StageCanvas(StagePanel* parent)
	: wxgui::SpriteStageCanvas(parent, parent)
{
}

void StageCanvas::onDraw()
{
	drawGuideLines();
	wxgui::SpriteStageCanvas::onDraw();
}

void StageCanvas::drawGuideLines()
{
	glPushMatrix();

	float hEdge, posOffset, posOffset1, rowOffset;
	static_cast<StagePanel*>(m_editPanel)->computeParams(hEdge, posOffset, posOffset1, rowOffset);

	glColor3f(LIGHT_GRAY.r, LIGHT_GRAY.g, LIGHT_GRAY.b);
	f2Vec2 base(hEdge, -posOffset1);
	for (size_t i = 0; i < Blackboard::row; ++i)
	{
		int col = (i % 2 ? Blackboard::col - 1 : Blackboard::col);
		for (size_t j = 0; j < col; ++j)
		{
			glBegin(GL_LINE_LOOP);
				glVertex2f(base.x - hEdge, base.y + posOffset);
				glVertex2f(base.x		 , base.y + posOffset1);
				glVertex2f(base.x + hEdge, base.y + posOffset);
				glVertex2f(base.x + hEdge, base.y - posOffset);
				glVertex2f(base.x		 , base.y - posOffset1);
				glVertex2f(base.x - hEdge, base.y - posOffset);
			glEnd();
			base.x += Blackboard::edge;
		}
		base.x = (i % 2 ? hEdge: Blackboard::edge);
		base.y -= rowOffset;
	}

	int width = Blackboard::edge * Blackboard::col,
	height = posOffset1 + rowOffset * (Blackboard::row - 1) + posOffset1;

	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_LINE_LOOP);
		glVertex2f(0.0f, 0.0f);
		glVertex2f(width, 0.0f);
		glVertex2f(width, -height);
		glVertex2f(0.0f, -height);
	glEnd();

	glPopMatrix();
}