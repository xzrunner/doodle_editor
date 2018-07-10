#include "StageCanvas.h"
#include "StagePanel.h"
#include "Blackboard.h"

#include "Frame/defs.h"

using namespace deditor::magic_defence;

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
		for (size_t i = 0; i <= Blackboard::row; ++i)
		{
			glVertex2f(0.0f, Blackboard::edge * i);
			glVertex2f(Blackboard::edge * Blackboard::length, Blackboard::edge * i);
		}
		glVertex2f(0.0f, 0.0f);
		glVertex2f(0.0f, Blackboard::edge * Blackboard::row);
		glVertex2f(Blackboard::edge * Blackboard::length, 0.0f);
		glVertex2f(Blackboard::edge * Blackboard::length, Blackboard::edge * Blackboard::row);
	glEnd();

	// calibration
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_LINES);
	const float secondEdge = (float) Blackboard::length / Blackboard::time;
	for (int i = 0; i <= Blackboard::time; ++i)
	{
		if (i % 5 == 0)
		{
			glVertex2f(Blackboard::edge * secondEdge * i, -Blackboard::edge * 3);
			glVertex2f(Blackboard::edge * secondEdge * i, 0.0f);
		}
		else
		{
			glVertex2f(Blackboard::edge * secondEdge * i, -Blackboard::edge);
			glVertex2f(Blackboard::edge * secondEdge * i, 0.0f);
		}
	}
	for (int i = 0, n = Blackboard::time / 10; i <= n; ++i)
	{
		if (i % 5 == 0)
		{
			glVertex2f(Blackboard::edge * secondEdge * i * 10, Blackboard::edge * Blackboard::row);
			glVertex2f(Blackboard::edge * secondEdge * i * 10, Blackboard::edge * Blackboard::row + Blackboard::edge * 3);
		}
		else
		{
			glVertex2f(Blackboard::edge * secondEdge * i * 10, Blackboard::edge * Blackboard::row);
			glVertex2f(Blackboard::edge * secondEdge * i * 10, Blackboard::edge * Blackboard::row + Blackboard::edge);
		}
	}
	glEnd();
}