#ifndef _FEDITOR_INTERFACE_PASTE_SPRITE_CALLBACK_H_
#define _FEDITOR_INTERFACE_PASTE_SPRITE_CALLBACK_H_

namespace FEDITOR
{
	class Sprite;

	class IPasteSpriteCB
	{
	public:
		virtual void afterAddSprite(Sprite* sprite) = 0;

	}; // IPasteSpriteCB
}

#endif // _FEDITOR_INTERFACE_PASTE_SPRITE_CALLBACK_H_