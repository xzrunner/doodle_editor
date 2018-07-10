#ifndef _DEDITOR_MOTOX_PASTE_TILE_CMPT_H_
#define _DEDITOR_MOTOX_PASTE_TILE_CMPT_H_

#include <wxGUI/wxGUI.h>

namespace deditor
{
	namespace motox
	{
		class StagePanel;
		class LibraryCombinationList;
		class LibraryTemplateList;

		class PasteTileCMPT : public wxgui::AbstractEditCMPT
		{
		public:
			PasteTileCMPT(wxWindow* parent, const wxString& name,
				StagePanel* editPanel, wxgui::LibraryPanel* libraryPanel);

		protected:
			virtual wxSizer* initLayout();

		}; // PasteTileCMPT
	}
}

#endif // _DEDITOR_MOTOX_PASTE_TILE_CMPT_H_