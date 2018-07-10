#ifndef _FEDITOR_ABSTRACT_ARRANGE_SPRITE_CALLBACK_H_
#define _FEDITOR_ABSTRACT_ARRANGE_SPRITE_CALLBACK_H_
#include <Fruits2D/Fruits2D.h>

namespace FEDITOR
{
	class Sprite;

	class AbstractArrangeSpriteCB
	{
	public:
		virtual void deleteSprite(Sprite* sprite) {}
		virtual void afterMoveSprite(Sprite* sprite) {}

		virtual void afterMouseLeftDown(const f2Vec2& pos) {}
		virtual void afterMouseLeftUp(const f2Vec2& pos) {}

	}; // AbstractArrangeSpriteCB 
}

#endif // _FEDITOR_ABSTRACT_ARRANGE_SPRITE_CALLBACK_H_