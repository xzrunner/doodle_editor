#ifndef _WX_GUI_LIBRARY_COMBINATION_PAGE_H_
#define _WX_GUI_LIBRARY_COMBINATION_PAGE_H_

#include "ILibraryPage.h"

namespace wxgui
{
	class LibraryCombinationPage : public ILibraryPage
	{
	public:
		LibraryCombinationPage(wxWindow* parent);

		virtual bool isHandleSymbol(ISymbol* symbol) const;

	protected:
		virtual void onAddPress(wxCommandEvent& event);

	}; // LibraryCombinationPage
}

#endif // _WX_GUI_LIBRARY_COMBINATION_PAGE_H_