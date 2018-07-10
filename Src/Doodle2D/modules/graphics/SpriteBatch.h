#ifndef _D2D_SPRITE_BATCH_H_
#define _D2D_SPRITE_BATCH_H_

#include "common/types.h"

namespace d2d
{
	class Texture;
	class Quad;
	class Color;
	class VertexBuffer;
	class GraphicsSprite;

	class SpriteBatch
	{
	public:
		enum UsageHint
		{
			USAGE_DYNAMIC = 1,
			USAGE_STATIC,
			USAGE_STREAM,
			USAGE_MAX_ENUM
		};

	public:
		SpriteBatch(Texture* texture, int size, int usage);
		virtual ~SpriteBatch();

	//	int add(const Quad& quad, int index = -1);
		int add(const GraphicsSprite& sprite, int index = -1);
		int add(const Quad& quad, float x, float y, float angle, 
			float scale, int index = -1);

		void* lock();
		void unlock();

		void setColor(const Color& color);
		void setColor();

		void onDraw() const;

		void setEndIndex(int iNext) { m_next = iNext; }

	private:
		void createBuffer(int size, int usage);
		void fillIndicesBuffer(int size);

		void add(const Vertex* v, int index);

		void setColor(Vertex* v, const Color& color);

	private:
		Texture* m_texture;

		int m_size;
		int m_next;

		Vertex m_sprite[4];

		Color* m_color;

		VertexBuffer* m_vertices;
		VertexBuffer* m_indices;

	}; // SpriteBatch
}

#endif // _D2D_SPRITE_BATCH_H_