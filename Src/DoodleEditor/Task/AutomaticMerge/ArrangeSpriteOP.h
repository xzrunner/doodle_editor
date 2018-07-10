#ifndef _DEDITOR_AUTOMATIC_MERGE_ARRANGE_SPRITE_OP_H_
#define _DEDITOR_AUTOMATIC_MERGE_ARRANGE_SPRITE_OP_H_

#include <wxGUI/wxGUI.h>

namespace deditor
{
	namespace automatic_merge
	{
		class StagePanel;

		class ArrangeSpriteOP : public wxgui::ArrangeSpriteOP<wxgui::SelectSpritesOP>
		{
		public:
			ArrangeSpriteOP(StagePanel* editPanel, 
				wxgui::PropertySettingPanel* propertyPanel,
				wxgui::AbstractEditCMPT* callback = NULL);

			virtual bool onMouseLeftUp(int x, int y);
			virtual bool onMouseRightDown(int x, int y);
			virtual bool onMouseRightUp(int x, int y);

			virtual bool onDraw() const;

		private:
			class FixCoordsVisitor : public IVisitor
			{
			public:
				virtual void visit(IObject* object, bool& bFetchNext);
			}; // FixCoordsVisitor

		private:
			StagePanel* m_editPanel;

		}; // ArrangeSpriteOP
	}
}

#endif // _DEDITOR_AUTOMATIC_MERGE_ARRANGE_SPRITE_OP_H_