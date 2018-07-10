#ifndef _DEDITOR_MOTOX_PASTE_TILE_TEMPLATE_CMPT_H_
#define _DEDITOR_MOTOX_PASTE_TILE_TEMPLATE_CMPT_H_

#include <wxGUI/wxGUI.h>

namespace deditor
{
	namespace motox
	{
		class StagePanel;
		class LibraryTemplateList;

		class PasteTileTemplateCMPT : public wxgui::AbstractEditCMPT
		{
		public:
			PasteTileTemplateCMPT(wxWindow* parent, const wxString& name,
				StagePanel* editPanel, wxgui::LibraryPanel* libraryPanel);

			bool isIndexRamdomOpen() const { return m_randomOpenCheck->IsChecked(); }

		protected:
			virtual wxSizer* initLayout();

		private:
			wxCheckBox* m_randomOpenCheck;

		}; // PasteTileTemplateCMPT
	}
}

#endif // _DEDITOR_MOTOX_PASTE_TILE_TEMPLATE_CMPT_H_