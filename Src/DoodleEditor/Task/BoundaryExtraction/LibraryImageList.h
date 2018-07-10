#ifndef _DEDITOR_BOUNDARY_EXTRACTION_LIBRARY_IMAGE_LIST_H_
#define _DEDITOR_BOUNDARY_EXTRACTION_LIBRARY_IMAGE_LIST_H_

#include <wxGUI/wxGUI.h>

namespace deditor
{
	namespace boundary_extraction
	{
		class StagePanel;
		class ToolbarPanel;

		class LibraryImageList : public wxgui::LibraryList
		{
		public:
			LibraryImageList(wxWindow* parent);

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

		}; // LibraryImageList
	}
}

#endif // _DEDITOR_BOUNDARY_EXTRACTION_LIBRARY_IMAGE_LIST_H_