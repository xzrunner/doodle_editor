#ifndef _D2D_ACTOR_H_
#define _D2D_ACTOR_H_

#include "Item.h"

namespace d2d
{
	class GraphicsSprite;

	class Actor : public Item
	{
	public:
		Actor(GraphicsSprite* sprite);

		virtual void onDraw() const;

	private:
		GraphicsSprite* m_sprite;

	}; // Actor
}

#endif // _D2D_ACTOR_H_