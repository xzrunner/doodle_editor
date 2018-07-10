#include "StageCanvas.h"
#include "StagePanel.h"
#include "Blackboard.h"

#include "Frame/defs.h"

using namespace deditor::monster;

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
	// background
	glColor3f(LIGHT_GRAY.r, LIGHT_GRAY.g, LIGHT_GRAY.b);
	glBegin(GL_LINES);
		glVertex2f(-Blackboard::edge * 3, 0.0f);
		glVertex2f(Blackboard::edge * Blackboard::col + Blackboard::edge * 3, 0.0f);
		for (size_t i = 0; i < Blackboard::row; ++i)
		{
			const float y = Blackboard::edge * (i + 1);
			glVertex2f(0.0f, -y);
			glVertex2f(Blackboard::edge * Blackboard::col, -y);
		}
		for (size_t i = 0; i <= Blackboard::col; ++i)
		{
			glVertex2f(Blackboard::edge * i, -Blackboard::edge * Blackboard::row);
			glVertex2f(Blackboard::edge * i,  Blackboard::edge * Blackboard::length);
		}
		glVertex2f(0.0f, Blackboard::edge * Blackboard::length);
		glVertex2f(Blackboard::edge * Blackboard::col, Blackboard::edge * Blackboard::length);
	glEnd();

	// calibration
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_LINES);
		const float secondEdge = (float) Blackboard::length / Blackboard::time;
		for (int i = 0; i <= Blackboard::time; ++i)
		{
			if (i % 5 == 0)
			{
				glVertex2f(-Blackboard::edge * 3, Blackboard::edge * secondEdge * i);
				glVertex2f(0.0f, Blackboard::edge * secondEdge * i);
			}
			else
			{
				glVertex2f(-Blackboard::edge, Blackboard::edge * secondEdge * i);
				glVertex2f(0.0f, Blackboard::edge * secondEdge * i);
			}
		}
		for (int i = 0, n = Blackboard::time / 10; i <= n; ++i)
		{
			if (i % 5 == 0)
			{
				glVertex2f(Blackboard::edge * Blackboard::col, Blackboard::edge * secondEdge * i * 10);
				glVertex2f(Blackboard::edge * Blackboard::col + Blackboard::edge * 3, Blackboard::edge * secondEdge * i * 10);
			}
			else
			{
				glVertex2f(Blackboard::edge * Blackboard::col, Blackboard::edge * secondEdge * i * 10);
				glVertex2f(Blackboard::edge * Blackboard::col + Blackboard::edge, Blackboard::edge * secondEdge * i * 10);
			}
		}
	glEnd();
}