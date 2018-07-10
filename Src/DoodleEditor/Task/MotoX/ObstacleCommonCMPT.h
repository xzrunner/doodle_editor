#ifndef _DEDITOR_MOTOX_OBSTACLE_COMMON_CMPT_H_
#define _DEDITOR_MOTOX_OBSTACLE_COMMON_CMPT_H_

#include <wxGUI/wxGUI.h>

namespace deditor
{
	namespace motox
	{
		class StagePanel;

		class ObstacleCommonCMPT : public wxgui::AbstractEditCMPT
		{
		public:
			ObstacleCommonCMPT(wxWindow* parent, const wxString& name,
				StagePanel* editPanel, wxgui::LibraryPanel* libraryPanel,
				wxgui::PropertySettingPanel* propertyPanel);

		protected:
			virtual wxSizer* initLayout();

		}; // ObstacleCommonCMPT
	}
}

#endif // _DEDITOR_MOTOX_OBSTACLE_COMMON_CMPT_H_