#ifndef _DEDITOR_MOTOX_ACTOR_EDIT_PARAMS_CMPT_H_
#define _DEDITOR_MOTOX_ACTOR_EDIT_PARAMS_CMPT_H_

#include <wxGUI/wxGUI.h>

namespace deditor
{
	namespace motox
	{
		class AEEditPanel;
		class AEJoints;

		class AEParamsCMPT : public wxgui::AbstractEditCMPT
		{
		public:
			AEParamsCMPT(wxWindow* parent, const wxString& name,
				AEEditPanel* editPanel);

			virtual void show(bool show);

		protected:
			virtual wxSizer* initLayout();

		private:
			void initChoicePanel(wxSizer* topSizer);
			void initSettingPanel(wxSizer* topSizer);
			void initSpeedPanel(wxSizer* topSizer);
			void initAnglePanel(wxSizer* topSizer);
			void initTorquePanel(wxSizer* topSizer);
			void initControlPanel(wxSizer* topSizer);

			void onChoiceChanged(wxCommandEvent& event);
			void onSettingChanged(wxCommandEvent& event);
			void onSetParams(wxSpinEvent& event);
			void onJointMotionPositive(wxCommandEvent& event);
			void onJointMotionNegative(wxCommandEvent& event);
			
		private:
			class SetBodyAliveVisitor : public IVisitor
			{
			public:
				SetBodyAliveVisitor(bool alive);

				virtual void visit(IObject* object, bool& bFetchNext);

			private:
				bool m_alive;

			}; // SetBodyAliveVisitor

		private:
			static const float SPEED_SCALE;
			static const float ANGLE_SCALE;

		private:
			AEJoints& m_joints;

			wxComboBox* m_jointChoice;
			wxCheckBox *m_checkLimit, *m_checkMotor;
			wxSpinCtrl *m_speedPositive, *m_speedNegative;
			wxSpinCtrl *m_angleLeftSmall, *m_angleLeftLarge,
				*m_angleRightSmall, *m_angleRightLarge;
			wxSpinCtrl *m_maxTroque;

		}; // AEParamsCMPT
	}
}

#endif // _DEDITOR_MOTOX_ACTOR_EDIT_PARAMS_CMPT_H_