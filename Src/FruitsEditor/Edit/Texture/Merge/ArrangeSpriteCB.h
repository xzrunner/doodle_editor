#ifndef _FEDITOR_ARRANGE_SPRITE_CALLBACK_H_
#define _FEDITOR_ARRANGE_SPRITE_CALLBACK_H_

#include "Edit/EditOperation/AbstractArrangeSpriteCB.h"

namespace FEDITOR
{
	namespace TEXTURE_MERGE
	{
		class Model;

		class ArrangeSpriteCB : public AbstractArrangeSpriteCB
		{
		public:
			ArrangeSpriteCB(Model* model);

			virtual void deleteSprite(Sprite* sprite);

		private:
			Model* m_model;

		}; // ArrangeSpriteCB 
	}
}

#endif // _FEDITOR_ARRANGE_SPRITE_CALLBACK_H_