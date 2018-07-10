#ifndef _FRUITS_ANIMATOR_ARRANGE_SPRITE_OP_H_
#define _FRUITS_ANIMATOR_ARRANGE_SPRITE_OP_H_

#include <wxGUI/wxGUI.h>

namespace FRUITS_ANIMATOR
{
	class StagePanel;

	class ArrangeSpriteOP : public wxgui::ArrangeSpriteOP
	{
	public:
		ArrangeSpriteOP(StagePanel* editPanel);

		virtual bool onMouseLeftDClick(int x, int y);

	private:
		StagePanel* m_editPanel;

	}; // ArrangeSpriteOP
}

#endif // _FRUITS_ANIMATOR_ARRANGE_SPRITE_OP_H_