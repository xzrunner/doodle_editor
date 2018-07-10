#ifndef _WX_GUI_ARRANGE_SPRITE_FIX_OP_H_
#define _WX_GUI_ARRANGE_SPRITE_FIX_OP_H_

#include "ArrangeSpriteOP.h"
#include "SelectSpritesOP.h"

namespace wxgui
{
	class ArrangeSpriteFixOP : public ArrangeSpriteOP<SelectSpritesOP>
	{
	public:
		ArrangeSpriteFixOP(EditPanel* editPanel, MultiSpritesImpl* spritesImpl,
			PropertySettingPanel* propertyPanel, AbstractEditCMPT* callback = NULL);

		virtual bool onMouseLeftUp(int x, int y);
		virtual bool onMouseRightDown(int x, int y);
		virtual bool onMouseRightUp(int x, int y);

	private:
		void fixSpritesLocation(const std::vector<ISprite*>& sprites);

	private:
		MultiSpritesImpl* m_spritesImpl;

	}; // ArrangeSpriteFixOP
}

#endif // _WX_GUI_ARRANGE_SPRITE_FIX_OP_H_