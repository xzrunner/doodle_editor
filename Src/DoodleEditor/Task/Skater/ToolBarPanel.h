#ifndef _DEDITOR_SKATER_TOOLBAR_PANEL_H_
#define _DEDITOR_SKATER_TOOLBAR_PANEL_H_

#include <wxGUI/wxGUI.h>

namespace deditor
{
	namespace skater
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

#endif // _DEDITOR_SKATER_TOOLBAR_PANEL_H_