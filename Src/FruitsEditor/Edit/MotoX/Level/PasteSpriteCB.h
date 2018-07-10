#ifndef _FEDITOR_MOTOX_LEVEL_PASTE_SPRITE_CALLBACK_H_
#define _FEDITOR_MOTOX_LEVEL_PASTE_SPRITE_CALLBACK_H_
#include "Edit/EditOperation/IPasteSpriteCB.h"

namespace FEDITOR
{
	class Layer;

	namespace MOTOX
	{
		namespace LEVEL
		{
			class Model;

			class PasteSpriteCB : public IPasteSpriteCB
			{
			public:
				PasteSpriteCB(Model* model);

				virtual void afterAddSprite(Sprite* sprite);

			private:
				Model* m_model;

			}; // PasteSpriteCB
		}
	}
}

#endif // _FEDITOR_MOTOX_LEVEL_PASTE_SPRITE_CALLBACK_H_