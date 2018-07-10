#ifndef _DEDITOR_MONSTER_SET_SPRITE_PROPERTY_CMPT_H_
#define _DEDITOR_MONSTER_SET_SPRITE_PROPERTY_CMPT_H_

#include <wxGUI/wxGUI.h>

namespace deditor
{
	namespace monster
	{
		class StagePanel;

		class SetSpritePropertyCMPT : public wxgui::AbstractEditCMPT
		{
		public:
			SetSpritePropertyCMPT(wxWindow* parent, const wxString& name,
				wxgui::PropertySettingPanel* propertyPanel, StagePanel* editPanel);

			virtual void updateControlValue();

		protected:
			virtual wxSizer* initLayout();

		private:
			void onChangeID(wxCommandEvent& event);

		private:
			class GetSpriteIDVisitor : public IVisitor
			{
			public:
				GetSpriteIDVisitor();
				virtual void visit(IObject* object, bool& bFetchNext);
				int getID() const { return m_id; }

			private:
				int m_id;	// FLOAT_MAX: don't have a same value

			}; // GetSpriteIDVisitor

			class SetSpriteIDVisitor : public IVisitor
			{
			public:
				SetSpriteIDVisitor(int id);
				virtual void visit(IObject* object, bool& bFetchNext);

			private:
				int m_id;

			}; // SetSpriteIDVisitor

		private:
			StagePanel* m_editPanel;

			wxTextCtrl* m_idCtrl;

		}; // SetSpritePropertyCMPT
	}
}

#endif // _DEDITOR_MONSTER_SET_SPRITE_PROPERTY_CMPT_H_