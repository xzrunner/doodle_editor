#ifndef _DEDITOR_BOUNDARY_EXTRACTION_LIBRARY_FILE_LIST_H_
#define _DEDITOR_BOUNDARY_EXTRACTION_LIBRARY_FILE_LIST_H_

#include <wxGUI/wxGUI.h>

namespace deditor
{
	namespace boundary_extraction
	{
		class StagePanel;
		class ToolbarPanel;

		class LibraryFileList : public wxgui::LibraryList
		{
		public:
			LibraryFileList(wxWindow* parent);

			//
			// ISerializable interface
			//
			virtual void loadFromTextFile(std::ifstream& fin);
			virtual void storeToTextFile(std::ofstream& fout) const;

			virtual void onListSelected(wxCommandEvent& event);

			void registerContext(StagePanel* stage, 
				ToolbarPanel* toolbar);

		private:
			StagePanel* m_stage;
			ToolbarPanel* m_toolbar;

		}; // LibraryFileList
	}
}

#endif // _DEDITOR_BOUNDARY_EXTRACTION_LIBRARY_FILE_LIST_H_