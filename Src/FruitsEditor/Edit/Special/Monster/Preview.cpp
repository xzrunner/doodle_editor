#include "Preview.h"
#include "Blackboard.h"
#include "Dataset/Sprite.h"
#include "Dataset/Layer.h"
#include "Render/Render.h"
// todo
#include <Windows.h>
#include <GL/GL.h>

using namespace FEDITOR;
using namespace FEDITOR::MONSTER;

const float Preview::LEFTMOST = - 960.0f;
const float Preview::COL_WIDTH = 480.0f / 7;

Preview::Preview(Blackboard* blackboard)
{
	m_blackboard = blackboard;
}

void Preview::load(Layer* layer)
{
	const std::vector<Sprite*>& sprites = layer->getAllSprites();
	m_sprites.clear();
	copy(sprites.begin(), sprites.end(), back_inserter(m_sprites));
}

void Preview::start()
{
	m_start = clock();
}

void Preview::step()
{
	drawView();
}

void Preview::drawView() const
{
	glClearStencil(0);
	glEnable(GL_STENCIL_TEST);

	glClear(GL_STENCIL_BUFFER_BIT);

	glStencilFunc(GL_NEVER, 0x0, 0x0);
	glStencilOp(GL_INCR, GL_INCR, GL_INCR);

	glBegin(GL_QUADS);
		glVertex3f(-960.0f, 0.0f, -1.0f);
		glVertex3f(-480.0f, 0.0f, -1.0f);
		glVertex3f(-480.0f, 800.0f, -1.0f);
		glVertex3f(-960.0f, 800.0f, -1.0f);
	glEnd();

	glStencilFunc(GL_NOTEQUAL, 0x0, 0x1);
	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);

	drawTotal();

	glDisable(GL_STENCIL_TEST);
}

void Preview::drawTotal() const
{
	float length = (m_blackboard->m_edge * m_blackboard->m_length) * 480.0f / (m_blackboard->m_edge * 7);
	float yBase = getYBase(length);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	for (size_t i = 0, n = m_sprites.size(); i < n; ++i)
	{
		Sprite* sprite = m_sprites[i];
		float* data = static_cast<float*>(sprite->getUserData());
		const float col = data[0], row = data[1];
		if (row > 0)
		{
			const float x = LEFTMOST + (col - 1) * COL_WIDTH + COL_WIDTH * 0.5f,
				y = yBase + length * row;

			glPushMatrix();
			glTranslatef(x, y, 1.0f);
			Render::drawTextures(sprite->getAllTextureRegions());
			glPopMatrix();
		}
	}

	glDisable(GL_BLEND);
}

float Preview::getYBase(float length) const
{
	float tot = m_blackboard->m_time * 1000.0f;
	float curr = clock() - m_start;
	if (curr > tot) 
		return 960.0f - length;

	float percent = curr / tot;
	return 800.0f - length * percent;
}