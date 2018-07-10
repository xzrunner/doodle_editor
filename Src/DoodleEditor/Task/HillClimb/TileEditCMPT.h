#ifndef _DEDITOR_HILL_CLIMB_TILE_EDIT_CMPT_H_
#define _DEDITOR_HILL_CLIMB_TILE_EDIT_CMPT_H_

#include <wxGUI/wxGUI.h>

namespace deditor
{
	namespace hill_climb
	{
		class StagePanel;

		class TileEditCMPT : public wxgui::AbstractEditCMPT
		{
		public:
			TileEditCMPT(wxWindow* parent, const wxString& name, StagePanel* editPanel, 
				wxgui::LibraryPanel* libraryPanel, wxgui::PropertySettingPanel* propertyPanel);

		protected:
			virtual wxSizer* initLayout();

		}; // TileEditCMPT
	}
}

#endif // _DEDITOR_HILL_CLIMB_TILE_EDIT_CMPT_H_