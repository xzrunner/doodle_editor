#include "Background.h"

#include "Tools/defs.h"

using namespace motox;

const size_t Background::TILE_COUNT = (size_t) std::ceil((float) d2d::SCREEN_WIDTH / (Background::TEXTURE_WIDTH / Background::COL)) + 1;
//const size_t Background::TILE_COUNT = 16;

Background::Background(d2d::Context* pContext)
{
	loadFromFile(pContext);
}

void Background::draw() const
{
	drawColor();
	m_batch->onDraw();
}

void Background::update(const d2d::Vector& center)
{
	updateTexture(center);
	updateColor(center);
}

void Background::loadFromFile(d2d::Context* pContext)
{
#ifdef D2D_WINDOWS
	std::string path = RESOURCE_ROOT + BACKGROUND_FILENAME;

	std::ifstream fin(path.c_str());
	if (fin.fail()) path = BACKGROUND_FILENAME;
	fin.close();
#elif defined D2D_ANDROID_NATIVE
	std::string path = BACKGROUND_FILENAME;
#elif defined D2D_ANDROID_JNI
	std::string path = BACKGROUND_FILENAME;
#endif

	d2d::Texture* texture = pContext->m_graphicsService->registerTexture(path);
	texture->load();
	m_batch = new d2d::SpriteBatch(texture, TILE_TOT_COUNT, d2d::SpriteBatch::USAGE_STATIC);

	int index = 0;
	for (size_t i = 0; i < ROW; ++i)
	{
		for (size_t j = 0; j < COL; ++j)
		{
			m_parts[index++] = new d2d::GraphicsSprite(texture, TILE_WIDTH * j, TILE_HEIGHT * i, TILE_WIDTH, TILE_HEIGHT, TEXTURE_WIDTH, TEXTURE_HEIGHT);
		}
	}

	for (size_t i = 0; i < TILE_COUNT; ++i)
		m_batch->add(*m_parts[0], -1);
}

void Background::drawColor() const
{
	glBindTexture(GL_TEXTURE_2D, NULL);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

	glVertexPointer(2, GL_FLOAT, 0, &m_vertices[0]);
	glColorPointer(4, GL_UNSIGNED_BYTE, 0, &m_colors[0].r);

	glDrawArrays(GL_TRIANGLE_STRIP, 0, 6);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
}

void Background::updateTexture(const d2d::Vector& center)
{
	m_batch->lock();

	const float left = center.x / SPEED_SLOWER_TIMES;
	const int tot_length = TEXTURE_WIDTH * ROW;
	const int dis_times = left / tot_length;
	const int leftIndex = (left - dis_times * tot_length) / TILE_WIDTH;
	const float xOffset = TILE_WIDTH * 0.5f + (center.x - left) - (d2d::SCREEN_WIDTH >> 1),
		yOffset = - (d2d::SCREEN_HEIGHT - TILE_HEIGHT) * 0.5f;
	for (size_t i = 0; i < TILE_COUNT; ++i)
	{
		int indexFixed = leftIndex + i;
		indexFixed = indexFixed >= TILE_TOT_COUNT ? indexFixed - TILE_TOT_COUNT : indexFixed;
		d2d::Vector pos;
		pos.x = tot_length * dis_times + TILE_WIDTH * (leftIndex + i) + xOffset;
		pos.y = center.y + yOffset;
		m_parts[indexFixed]->setTransform(pos, 0);
		m_batch->add(*m_parts[indexFixed], i);
	}

	m_batch->unlock();
}

void Background::updateColor(const d2d::Vector& center)
{
	const int HALF_WIDTH = d2d::SCREEN_WIDTH >> 1,
		HALF_HEIGHT = d2d::SCREEN_HEIGHT >> 1;
	const float midHeight = d2d::SCREEN_HEIGHT * 0.85f;

	int index = 0;

	m_vertices[index++] = center.x - HALF_WIDTH;
	m_vertices[index++] = center.y - HALF_HEIGHT + TILE_HEIGHT;

	m_vertices[index++] = center.x + HALF_WIDTH;
	m_vertices[index++] = center.y - HALF_HEIGHT + TILE_HEIGHT;

	m_vertices[index++] = center.x - HALF_WIDTH;
	m_vertices[index++] = center.y - HALF_HEIGHT + midHeight;

	m_vertices[index++] = center.x + HALF_WIDTH;
	m_vertices[index++] = center.y - HALF_HEIGHT + midHeight;

	m_vertices[index++] = center.x - HALF_WIDTH;
	m_vertices[index++] = center.y + HALF_HEIGHT;
	
	m_vertices[index++] = center.x + HALF_WIDTH;
	m_vertices[index++] = center.y + HALF_HEIGHT;

	//////////////////////////////////////////////////////////////////////////

	d2d::Color low(152, 214, 246, 255), up(0, 73, 126, 255), mid, lowFix;

	mid.r = up.r + (low.r - up.r) * 0.85f;
	mid.g = up.g + (low.g - up.g) * 0.85f;
	mid.b = up.b + (low.b - up.b) * 0.85f;
	mid.a = 255;

	const float factor = TILE_HEIGHT / d2d::SCREEN_HEIGHT * 0.85f;
	lowFix.r = low.r + (mid.r - low.r) * factor;
	lowFix.g = low.g + (mid.g - low.g) * factor;
	lowFix.b = low.b + (mid.b - low.b) * factor;
	lowFix.a = 255;

	index = 0;
	m_colors[index++] = lowFix;
	m_colors[index++] = lowFix;
	m_colors[index++] = mid;
	m_colors[index++] = mid;
	m_colors[index++] = up;
	m_colors[index++] = up;
}