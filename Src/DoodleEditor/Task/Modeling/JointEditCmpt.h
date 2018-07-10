#ifndef _DEDITOR_MODELING_JOINT_EDIT_CMPT_H_
#define _DEDITOR_MODELING_JOINT_EDIT_CMPT_H_

#include <wxGUI/wxGUI.h>

namespace deditor
{
	namespace modeling
	{
		class StagePanel;

		class JointEditCmpt : public wxgui::AbstractEditCMPT
		{
		public:
			JointEditCmpt(wxWindow* parent, const wxString& name,
				StagePanel* editPanel, wxgui::PropertySettingPanel* propertyPanel);

			virtual void updateControlValue();

		protected:
			virtual wxSizer* initLayout();

		private:
			void onCreateJoint(wxCommandEvent& event);

//			void createJointsSizer();

// 			wxSizer* createRevoluteJointSizer() const;
// 			wxSizer* createWheelJointSizer() const;

		private:
			class SelectWheelDialog : public wxDialog
			{
			public:
				SelectWheelDialog(wxWindow* parent, const wxString& title, 
					const wxString& body0, const wxString& body1);

				int getChoice() const {
					return m_wheelChoice->GetSelection();
				}

			private:
				void initLayout(const wxString& body0, const wxString& body1);

			private:
				wxChoice* m_wheelChoice;

			}; // SelectWheelDialog

		private:
			wxChoice* m_typeChoice;

			wxButton* m_btnOK;

//			std::vector<wxSizer*> m_jointsSizer;

		}; // JointEditCmpt
	}
}

#endif // _DEDITOR_MODELING_JOINT_EDIT_CMPT_H_