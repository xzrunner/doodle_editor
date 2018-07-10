#ifndef _D2D_SCALE_SIZE_H_
#define _D2D_SCALE_SIZE_H_

#include "Behavior.h"

namespace d2d
{
	class GraphicsSprite;

	class ScaleSize : public Behavior
	{
	public:
		ScaleSize(GraphicsSprite* sprite, float scale);

		virtual void trigger();

	private:
		GraphicsSprite* m_sprite;

		float m_scale;

	}; // ScaleSize
}

#endif // _D2D_SCALE_SIZE_H_