#ifndef _DEDITOR_MOTOX_LIBRARY_COMBINATION_PAGE_H_
#define _DEDITOR_MOTOX_LIBRARY_COMBINATION_PAGE_H_

#include <wxGUI/wxGUI.h>

namespace deditor
{
	namespace motox
	{
		class LibraryCombinationPage : public wxgui::ILibraryPage
		{
		public:
			LibraryCombinationPage(wxWindow* parent);

			virtual bool isHandleSymbol(wxgui::ISymbol* symbol) const;

		protected:
			virtual void onAddPress(wxCommandEvent& event);

		}; // LibraryCombinationPage
	}
}

#endif // _DEDITOR_MOTOX_LIBRARY_COMBINATION_PAGE_H_