#ifndef _D2D_GRAPHICS_SPRITE_H_
#define _D2D_GRAPHICS_SPRITE_H_

#include "Quad.h"

#include "common/Vector.h"

namespace d2d
{
	class Texture;

	class GraphicsSprite
	{
	public:
		GraphicsSprite(Texture* pTexture);
		GraphicsSprite(Texture* pTexture, int left, int top, int width, int height,
			int totWidth, int totHeight, float scale = 1.0f);

 		void onDraw() const;

		void translate(const Vector& offset);
		void rotate(float delta);
		void setTransform(const Vector& location, float angle);
		void setScale(float scale);
		void setMirror(bool xMirror, bool yMirror);

		const Vector& getLocation() const { return m_location; }
		float getAngle() const { return m_angle; }
		float getScale() const { return m_scale; }

		Texture* getTexture() { return m_texture; }
		const Quad& getQuad() const { return m_quad; }

	protected:
		Vector m_location;
		float m_angle;
		float m_scale;

		bool m_xMirror, m_yMirror;

		Texture* m_texture;
		Quad m_quad;

	}; // GraphicsSprite
}

#endif // _D2D_GRAPHICS_SPRITE_H_