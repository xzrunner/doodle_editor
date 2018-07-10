#ifndef _DEDITOR_MOTOX_LIBRARY_BREAKABLE_PAGE_H_
#define _DEDITOR_MOTOX_LIBRARY_BREAKABLE_PAGE_H_

#include <wxGUI/wxGUI.h>

namespace deditor
{
	namespace motox
	{
		class LibraryBreakablePage : public wxgui::ILibraryPage
		{
		public:
			LibraryBreakablePage(wxWindow* parent);

			virtual bool isHandleSymbol(wxgui::ISymbol* symbol) const;

		protected:
			virtual void onAddPress(wxCommandEvent& event);

		}; // LibraryBreakablePage
	}
}

#endif // _DEDITOR_MOTOX_LIBRARY_BREAKABLE_PAGE_H_