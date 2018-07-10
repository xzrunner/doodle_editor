#ifndef _DEDITOR_MOTOX_ACTOR_EDIT_PARTS_OP_H_
#define _DEDITOR_MOTOX_ACTOR_EDIT_PARTS_OP_H_

#include "AEParts.h"

#include <wxGUI/wxGUI.h>

namespace deditor
{
	namespace motox
	{
		class AEEditPanel;
		class AEPartsCMPT;

		class AEPartsOP : public wxgui::ArrangeSpriteOP<wxgui::SelectSpritesOP>
		{
		public:
			AEPartsOP(AEEditPanel* editPanel, AEPartsCMPT* cmpt,
				wxgui::PropertySettingPanel* propertyPanel);

			virtual bool onMouseLeftDown(int x, int y);
			virtual bool onMouseLeftUp(int x, int y);

			void loadPart(wxgui::ISymbol* symbol, const f2Vec2& pos);

 		protected:
 			virtual void translateSprite(const f2Vec2& delta);
 			virtual void rotateSprite(const f2Vec2& dst);

		private:
			void afterSpriteArrange();
			void resetSelectionToPart();

		private:
			class UpdateVisitor : public IVisitor
			{
			public:
				UpdateVisitor(AEParts& parts);

				virtual void visit(IObject* object, bool& bFetchNext);

			private:
				void update(wxgui::ISprite* changed, int id0, int id1);

			private:
				AEParts& m_parts;

			}; // UpdateVisitor

		private:
			AEParts& m_parts;

			AEPartsCMPT* m_cmpt;

		}; // AEPartsOP
	}
}

#endif // _DEDITOR_MOTOX_ACTOR_EDIT_PARTS_OP_H_