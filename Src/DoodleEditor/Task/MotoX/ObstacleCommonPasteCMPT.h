#ifndef _DEDITOR_MOTOX_OBSTACLE_COMMON_PASTE_CMPT_H_
#define _DEDITOR_MOTOX_OBSTACLE_COMMON_PASTE_CMPT_H_

#include <wxGUI/wxGUI.h>

namespace deditor
{
	namespace motox
	{
		class StagePanel;

		class ObstacleCommonPasteCMPT : public wxgui::AbstractEditCMPT
		{
		public:
			ObstacleCommonPasteCMPT(wxWindow* parent, const wxString& name,
				StagePanel* editPanel, wxgui::LibraryPanel* libraryPanel);

		protected:
			virtual wxSizer* initLayout();

		private:
			void onChangeScale(wxSpinEvent& event);

		private:
			float m_scaleVal;

		}; // ObstacleCommonPasteCMPT
	}
}

#endif // _DEDITOR_MOTOX_OBSTACLE_COMMON_PASTE_CMPT_H_