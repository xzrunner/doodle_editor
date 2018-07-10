#ifndef _WX_GUI_SPRITE_FACTORY_H_
#define _WX_GUI_SPRITE_FACTORY_H_

#include "ISymbol.h"

#include <Fruits2D/Fruits2D.h>

namespace wxgui
{
	class ISprite;

	class SpriteFactory
	{
	public:
		static ISprite* create(ISymbol* symbol);

	}; // SpriteFactory
}

#endif // _WX_GUI_SPRITE_FACTORY_H_