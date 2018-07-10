#ifndef _DEDITOR_BOUNDARY_EXTRACTION_TOOLBAR_PANEL_H_
#define _DEDITOR_BOUNDARY_EXTRACTION_TOOLBAR_PANEL_H_

#include <wxGUI/wxGUI.h>

namespace deditor
{
	namespace boundary_extraction
	{
		class StagePanel;
		class LibraryItem;

		class ToolbarPanel : public wxgui::ToolbarPanel
		{
		public:
			ToolbarPanel(wxWindow* parent, StagePanel* editPanel);

			void changeCurrItem(LibraryItem* item);

		protected:
			virtual wxSizer* initLayout();

		private:
			void onSetClose(wxCommandEvent& event);
			void onClearLines(wxCommandEvent& event);

		}; // ToolbarPanel
	}
}

#endif // _DEDITOR_BOUNDARY_EXTRACTION_TOOLBAR_PANEL_H_