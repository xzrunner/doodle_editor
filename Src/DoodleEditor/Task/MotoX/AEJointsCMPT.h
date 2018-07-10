#ifndef _DEDITOR_MOTOX_ACTOR_EDIT_JOINTS_CMPT_H_
#define _DEDITOR_MOTOX_ACTOR_EDIT_JOINTS_CMPT_H_

#include <wxGUI/wxGUI.h>

namespace deditor
{
	namespace motox
	{
		class AEEditPanel;

		class AEJointsCMPT : public wxgui::AbstractEditCMPT
		{
		public:
			enum ID
			{
				e_Neck,
				e_Shoulder,
				e_Elbow,
				e_Hip,
				e_Knee,
				e_Hand,
				e_Foot
			};

		public:
			AEJointsCMPT(wxWindow* parent, const wxString& name,
				AEEditPanel* editPanel);

			ID getSelectedID() const { 
				return static_cast<ID>(m_jointChoice->GetSelection()); 
			}

		protected:
			virtual wxSizer* initLayout();

		private:
			void onCreateAll(wxCommandEvent& event);

		private:
			AEEditPanel* m_editPanel;

			wxComboBox* m_jointChoice;

		}; // AEJointsCMPT
	}
}

#endif // _DEDITOR_MOTOX_ACTOR_EDIT_JOINTS_CMPT_H_