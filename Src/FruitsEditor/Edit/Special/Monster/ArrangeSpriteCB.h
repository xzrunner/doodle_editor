#ifndef _FEDITOR_MONSTER_ARRANGE_SPRITE_CALLBACK_H_
#define _FEDITOR_MONSTER_ARRANGE_SPRITE_CALLBACK_H_
#include "Edit/EditOperation/AbstractArrangeSpriteCB.h"

namespace FEDITOR
{
	class Layer;

	namespace MONSTER
	{
		class Blackboard;

		class ArrangeSpriteCB : public AbstractArrangeSpriteCB
		{
		public:
			ArrangeSpriteCB(Layer* layer, Blackboard* blackboard);

			virtual void afterMoveSprite(Sprite* sprite);

			virtual void afterMouseLeftUp(const f2Vec2& pos);

		private:
			Layer* m_layer;
			Blackboard* m_blackboard;

			Sprite* m_sprite;

		}; // ArrangeSpriteCB
	}
} 

#endif // _FEDITOR_MONSTER_ARRANGE_SPRITE_CALLBACK_H_