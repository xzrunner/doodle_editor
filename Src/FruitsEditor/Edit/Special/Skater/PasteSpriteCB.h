#ifndef _FEDITOR_SKATER_PASTE_SPRITE_CALLBACK_H_
#define _FEDITOR_SKATER_PASTE_SPRITE_CALLBACK_H_
#include "Edit/EditOperation/IPasteSpriteCB.h"

namespace FEDITOR
{
	class Sprite;

	namespace SKATER
	{
		class BoundsContainer;

		class PasteSpriteCB : public IPasteSpriteCB
		{
		public:
			PasteSpriteCB(const BoundsContainer& bounds);

			virtual void afterAddSprite(Sprite* sprite);

		private:
			void addUserData(Sprite* sprite);
			void addSpriteBound(Sprite* sprite);

		private:
			const BoundsContainer& m_bounds;

		}; // PasteSpriteCB
	}
}

#endif // _FEDITOR_SKATER_PASTE_SPRITE_CALLBACK_H_