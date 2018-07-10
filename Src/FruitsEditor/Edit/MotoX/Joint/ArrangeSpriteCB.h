#ifndef _FEDITOR_MOTOX_JOINT_ARRANGE_SPRITE_CALLBACK_H_
#define _FEDITOR_MOTOX_JOINT_ARRANGE_SPRITE_CALLBACK_H_
#include "../../EditOperation/AbstractArrangeSpriteCB.h"

namespace FEDITOR
{
	class AbstractArrangeSpriteCB;

	namespace MOTOX
	{
		namespace JOINT
		{
			class Parts;

			class ArrangeSpriteCB : public AbstractArrangeSpriteCB
			{
			public:
				ArrangeSpriteCB(Parts& parts);

				virtual void afterMoveSprite(Sprite* sprite);

			private:
				Parts& m_parts;

			}; // ArrangeSpriteCB
		}
	}
}

#endif // _FEDITOR_MOTOX_JOINT_ARRANGE_SPRITE_CALLBACK_H_