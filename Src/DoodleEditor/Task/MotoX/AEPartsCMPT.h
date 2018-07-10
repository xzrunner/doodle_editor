#ifndef _DEDITOR_MOTOX_ACTOR_EDIT_PARTS_CMPT_H_
#define _DEDITOR_MOTOX_ACTOR_EDIT_PARTS_CMPT_H_

#include <wxGUI/wxGUI.h>

namespace deditor
{
	namespace motox
	{
		class AEEditPanel;

		class AEPartsCMPT : public wxgui::AbstractEditCMPT
		{
		public:
			enum ID
			{
				e_Head,
				e_Body,
				e_BigArm,
				e_SmallArm,
				e_BigLeg,
				e_SmallLeg,
				e_FrontWheel,
				e_BackWheel,
				e_Motorbike
			};

		public:
			AEPartsCMPT(wxWindow* parent, const wxString& name,
				AEEditPanel* editPanel, wxgui::PropertySettingPanel* propertyPanel);

			ID getSelectedID() const { 
				return static_cast<ID>(m_partChoice->GetSelection()); 
			}

		protected:
			virtual wxSizer* initLayout();

		private:
			wxComboBox* m_partChoice;

		}; // AEPartsCMPT
	}
}

#endif // _DEDITOR_MOTOX_ACTOR_EDIT_PARTS_CMPT_H_