#ifndef _DEDITOR_BOUNDARY_EXTRACTION_LIBRARY_IMAGE_PAGE_H_
#define _DEDITOR_BOUNDARY_EXTRACTION_LIBRARY_IMAGE_PAGE_H_

#include <wxGUI/wxGUI.h>

namespace deditor
{
	namespace boundary_extraction
	{
		class LibraryImagePage : public wxgui::ILibraryPage
		{
		public:
			LibraryImagePage(wxWindow* parent);

			//
			// ISerializable interface
			//
			virtual void loadFromTextFile(std::ifstream& fin);
			virtual void storeToTextFile(std::ofstream& fout) const;

			virtual bool isHandleSymbol(wxgui::ISymbol* symbol) const;

			void clickListSelection();

		protected:
			virtual void onAddPress(wxCommandEvent& event);

		}; // LibraryImagePage
	}
}

#endif // _DEDITOR_BOUNDARY_EXTRACTION_LIBRARY_IMAGE_PAGE_H_