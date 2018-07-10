#ifndef _MOTOX_BACKGROUND_H_
#define _MOTOX_BACKGROUND_H_

#include <Doodle2D/doodle2d.h>

namespace motox
{
	class Background
	{
	public:
		Background(d2d::Context* pContext);

		void draw() const;
		void update(const d2d::Vector& center);

	private:
		void loadFromFile(d2d::Context* pContext);

		void drawColor() const;

		void updateTexture(const d2d::Vector& center);
		void updateColor(const d2d::Vector& center);

	private:
		static const int ROW = 2;
		static const int COL = 16;

		static const int TEXTURE_WIDTH = 1024;
		static const int TEXTURE_HEIGHT = 512;

		static const int TILE_WIDTH = TEXTURE_WIDTH / COL;
		static const int TILE_HEIGHT = TEXTURE_HEIGHT / ROW;

		static const size_t TILE_TOT_COUNT = ROW * COL;
		static const size_t TILE_COUNT;

		static const int SPEED_SLOWER_TIMES = 10;

	private:
		static const int VERTICES_SIZE = 6;

	private:
		d2d::SpriteBatch* m_batch;

		d2d::GraphicsSprite* m_parts[TILE_TOT_COUNT];

		float m_vertices[VERTICES_SIZE * 2];
		d2d::Color m_colors[VERTICES_SIZE];

	}; // Background
}

#endif // _MOTOX_BACKGROUND_H_