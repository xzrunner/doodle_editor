#ifndef _DEDITOR_SKATER_ARRANGE_SPRITE_OP_H_
#define _DEDITOR_SKATER_ARRANGE_SPRITE_OP_H_

#include <wxGUI/wxGUI.h>

namespace deditor
{
	namespace skater
	{
		class StagePanel;

		class ArrangeSpriteOP : public wxgui::ArrangeSpriteOP<wxgui::SelectSpritesOP>
		{
		public:
			ArrangeSpriteOP(StagePanel* editPanel,
				wxgui::PropertySettingPanel* propertyPanel,
				wxgui::AbstractEditCMPT* callback);

			virtual bool onMouseLeftDClick(int x, int y);

		private:
			StagePanel* m_editPanel;

		}; // ArrangeSpriteOP
	}
}

#endif // _DEDITOR_SKATER_ARRANGE_SPRITE_OP_H_