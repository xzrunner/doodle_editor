#ifndef _DEDITOR_MOTOX_PASTE_TILE_RANDOM_CMPT_H_
#define _DEDITOR_MOTOX_PASTE_TILE_RANDOM_CMPT_H_

#include <wxGUI/wxGUI.h>

namespace deditor
{
	namespace motox
	{
		class StagePanel;

		class PasteTileRandomCMPT : public wxgui::AbstractEditCMPT
		{
		public:
			PasteTileRandomCMPT(wxWindow* parent, const wxString& name,
				StagePanel* editPanel, wxgui::LibraryPanel* libraryPanel);

		protected:
			virtual wxSizer* initLayout();

		private:
			wxgui::PasteSymbolRandomWidget* m_randomWidget;

		}; // PasteTileRandomCMPT
	}
}

#endif // _DEDITOR_MOTOX_PASTE_TILE_RANDOM_CMPT_H_