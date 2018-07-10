#ifndef _DEDITOR_MOTOX_OBSTACLE_BREAKABLE_CMPT_H_
#define _DEDITOR_MOTOX_OBSTACLE_BREAKABLE_CMPT_H_

#include <wxGUI/wxGUI.h>

namespace deditor
{
	namespace motox
	{
		class StagePanel;

		class ObstacleBreakableCMPT : public wxgui::AbstractEditCMPT
		{
		public:
			ObstacleBreakableCMPT(wxWindow* parent, const wxString& name,
				StagePanel* editPanel, wxgui::LibraryPanel* libraryPanel,
				wxgui::PropertySettingPanel* propertyPanel);

		protected:
			virtual wxSizer* initLayout();

		private:
			void onChangeStaticType(wxCommandEvent& event);

		}; // ObstacleBreakableCMPT
	}
}

#endif // _DEDITOR_MOTOX_OBSTACLE_BREAKABLE_CMPT_H_