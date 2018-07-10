#ifndef _FEDITOR_MONSTER_PASTE_SPRITE_CALLBACK_H_
#define _FEDITOR_MONSTER_PASTE_SPRITE_CALLBACK_H_
#include "Edit/EditOperation/IPasteSpriteCB.h"

namespace FEDITOR
{
	class Layer;

	namespace MONSTER
	{
		class Blackboard;

		class PasteSpriteCB : public IPasteSpriteCB
		{
		public:
			PasteSpriteCB(Layer* layer, Blackboard* blackboard);

			virtual void afterAddSprite(Sprite* sprite);

		private:
			Layer* m_layer;
			Blackboard* m_blackboard;

		}; // PasteSpriteCB
	}
}

#endif // _FEDITOR_MONSTER_PASTE_SPRITE_CALLBACK_H_
