#ifndef _DEDITOR_HILL_CLIMB_STAGE_PANEL_H_
#define _DEDITOR_HILL_CLIMB_STAGE_PANEL_H_

#include <wxGUI/wxGUI.h>

namespace deditor
{
	namespace hill_climb
	{
		class StagePanel : public wxgui::EditPanel, public wxgui::ShapesPanelImpl, 
			public wxgui::SpritesPanelImpl
		{
		public:
			StagePanel(wxWindow* parent, wxgui::LibraryPanel* libraryPanel);

			virtual void clear();

		}; // StagePanel
	}
}

#endif // _DEDITOR_HILL_CLIMB_STAGE_PANEL_H_