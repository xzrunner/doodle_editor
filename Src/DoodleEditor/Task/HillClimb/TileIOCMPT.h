#ifndef _DEDITOR_HILL_CLIMB_TILE_IO_CMPT_H_
#define _DEDITOR_HILL_CLIMB_TILE_IO_CMPT_H_

#include <wxGUI/wxGUI.h>

namespace deditor
{
	namespace hill_climb
	{
		class StagePanel;

		class TileIOCMPT : public wxgui::AbstractEditCMPT
		{
		public:
			TileIOCMPT(wxWindow* parent, const wxString& name,
				StagePanel* editPanel, wxgui::LibraryPanel* libraryPanel);

		protected:
			virtual wxSizer* initLayout();

		private:
			void onLoadText(wxCommandEvent& event);
			void onStoreText(wxCommandEvent& event);

			void loadFromTextFile(const wxString& filepath);
			void storeToTextFile(const wxString& filepath) const;

		private:
			wxgui::LibraryPanel* m_libraryPanel;

		}; // TileIOCMPT
	}
}

#endif // _DEDITOR_HILL_CLIMB_TILE_IO_CMPT_H_