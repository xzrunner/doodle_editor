#ifndef _DEDITOR_MOTOX_MOTORBIKE_CMPT_H_
#define _DEDITOR_MOTOX_MOTORBIKE_CMPT_H_

#include <wxGUI/wxGUI.h>

namespace deditor
{
	namespace motox
	{
		class StagePanel;

		class MotorbikeCMPT : public wxgui::AbstractEditCMPT
		{
		public:
			MotorbikeCMPT(wxWindow* parent, const wxString& name,
				StagePanel* editPanel);

		protected:
			virtual wxSizer* initLayout();

		private:
			wxSizer* initControlPanel();
			wxSizer* initMotoSettingsPanel();
			wxSizer* initPlayerSettingsPanel();
			wxSizer* initTrackSettingsPanel();

			void onActiveMotoBike(wxCommandEvent& event);
			void onSetCameraFocus(wxCommandEvent& event);
			void onSetGravity(wxSpinEvent& event);

			void onWheelFrictionChanged(wxSpinEvent& event);
			void onMotoDensityChanged(wxSpinEvent& event);
			void onSpeedChanged(wxSpinEvent& event);
			void onAccelerationChanged(wxSpinEvent& event);
			void onMotorTorqueChanged(wxSpinEvent& event);

			void onPlayerDensityChanged(wxSpinEvent& event);
			void onPlayerTorqueChanged(wxSpinEvent& event);

			void onTrackFrictionChanged(wxSpinEvent& event);

		private:
			StagePanel* m_editPanel;

		}; // MotorbikeCMPT
	}
}

#endif // _DEDITOR_MOTOX_MOTORBIKE_CMPT_H_