#ifndef _DEDITOR_COMPRESS_PICTURE_LIBRARY_SYMBOL_LIST_H_
#define _DEDITOR_COMPRESS_PICTURE_LIBRARY_SYMBOL_LIST_H_

#include <wxGUI/wxGUI.h>

namespace deditor
{
	namespace compress_pictures
	{
		class StagePanel;
		class ToolbarPanel;
		struct CompressParams;

		class LibrarySymbolList : public wxgui::LibraryList
		{
		public:
			LibrarySymbolList(wxWindow* parent);

			void compressAll(const CompressParams& params, const wxString& ext) const;

			virtual void onListSelected(wxCommandEvent& event);

			void registerContext(StagePanel* stage, 
				ToolbarPanel* toolbar);

		private:
			StagePanel* m_stage;
			ToolbarPanel* m_toolbar;

		}; // LibrarySymbolList
	}
}

#endif // _DEDITOR_COMPRESS_PICTURE_LIBRARY_SYMBOL_LIST_H_