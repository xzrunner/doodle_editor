#ifndef _DEDITOR_HILL_CLIMB_TOOLBAR_PANEL_H_
#define _DEDITOR_HILL_CLIMB_TOOLBAR_PANEL_H_

#include <wxGUI/wxGUI.h>

namespace deditor
{
	namespace hill_climb
	{
		class StagePanel;

		class ToolbarPanel : public wxgui::ToolbarPanel
		{
		public:
			ToolbarPanel(wxWindow* parent, StagePanel* editPanel,
				wxgui::LibraryPanel* libraryPanel,
				wxgui::PropertySettingPanel* propertyPanel);

		protected:
			virtual wxSizer* initLayout();

		}; // ToolbarPanel 
	}
}

#endif // _DEDITOR_HILL_CLIMB_TOOLBAR_PANEL_H_