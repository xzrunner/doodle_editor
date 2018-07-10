#ifndef _DEDITOR_BOUNDARY_EXTRACTION_LIBRARY_FILE_PAGE_H_
#define _DEDITOR_BOUNDARY_EXTRACTION_LIBRARY_FILE_PAGE_H_

#include <wxGUI/wxGUI.h>

namespace deditor
{
	namespace boundary_extraction
	{
		class LibraryFilePage : public wxgui::ILibraryPage
		{
		public:
			LibraryFilePage(wxWindow* parent);

			//
			// ISerializable interface
			//
			virtual void loadFromTextFile(std::ifstream& fin);
			virtual void storeToTextFile(std::ofstream& fout) const;

			virtual bool isHandleSymbol(wxgui::ISymbol* symbol) const;

			void clickListSelection();

		protected:
			virtual void onAddPress(wxCommandEvent& event);

		}; // LibraryFilePage
	}
}

#endif // _DEDITOR_BOUNDARY_EXTRACTION_LIBRARY_FILE_PAGE_H_