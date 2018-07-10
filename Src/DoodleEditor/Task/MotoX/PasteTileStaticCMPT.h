#ifndef _DEDITOR_MOTOX_PASTE_TILE_STATIC_CMPT_H_
#define _DEDITOR_MOTOX_PASTE_TILE_STATIC_CMPT_H_

#include <wxGUI/wxGUI.h>

namespace deditor
{
	namespace motox
	{
		class StagePanel;

		class PasteTileStaticCMPT : public wxgui::AbstractEditCMPT
		{
		public:
			PasteTileStaticCMPT(wxWindow* parent, const wxString& name,
				StagePanel* editPanel, wxgui::LibraryPanel* libraryPanel);

		protected:
			virtual wxSizer* initLayout();

		private:
			void onChangeScale(wxSpinEvent& event);

		private:
			float m_scaleVal;

		}; // PasteTileStaticCMPT
	}
}

#endif // _DEDITOR_MOTOX_PASTE_TILE_STATIC_CMPT_H_