#ifndef _DEDITOR_MODELING_SELECT_BODY_OP_H_
#define _DEDITOR_MODELING_SELECT_BODY_OP_H_

#include <wxGUI/wxGUI.h>

namespace deditor
{
	namespace modeling
	{
		class BodyData;

		class SelectBodyOP : public wxgui::SelectSpritesOP
		{
		public:
			SelectBodyOP(wxgui::EditPanel* editPanel, 
				wxgui::MultiSpritesImpl* spritesImpl, 
				wxgui::PropertySettingPanel* propertyPanel, 
				wxgui::AbstractEditCMPT* callback = NULL,
				const f2Colorf& color = f2Colorf(1, 1, 1));

			virtual bool onKeyDown(int keyCode);
			virtual bool onMouseMove(int x, int y);

			virtual bool onDraw() const;
			virtual bool clear();

			virtual wxgui::IPropertySetting* createPropertySetting(wxgui::ISprite* sprite) const;

		private:
			class DrawSelectedVisitor : public IVisitor
			{
			public:
				virtual void visit(IObject* object, bool& bFetchNext);

			}; // DrawSelectedVisitor

		private:
			BodyData* m_mouseOn;

		}; // SelectBodyOP
	}
}

#endif // _DEDITOR_MODELING_SELECT_BODY_OP_H_