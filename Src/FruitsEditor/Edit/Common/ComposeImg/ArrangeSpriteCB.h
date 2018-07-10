#ifndef _FEDITOR_COMPOSE_IMG_ARRANGE_SPRITE_CALLBACK_H_
#define _FEDITOR_COMPOSE_IMG_ARRANGE_SPRITE_CALLBACK_H_
#include "Edit/EditOperation/AbstractArrangeSpriteCB.h"

namespace FEDITOR
{
	class CoordinateAxesCmpt;

	namespace COMPOSE_IMG
	{
		class ArrangeSpriteCB : public AbstractArrangeSpriteCB
		{
		public:
			ArrangeSpriteCB(CoordinateAxesCmpt* coordsCmpt);
			
			virtual void afterMoveSprite(Sprite* sprite);

		private:
			CoordinateAxesCmpt* m_coordsCmpt;

		}; // ArrangeSpriteCB
	}
}

#endif // _FEDITOR_COMPOSE_IMG_ARRANGE_SPRITE_CALLBACK_H_