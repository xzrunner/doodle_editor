#ifndef _WX_GUI_LIBRARY_SHAPE_PAGE_H_
#define _WX_GUI_LIBRARY_SHAPE_PAGE_H_

#include "ILibraryPage.h"

namespace wxgui
{
	class LibraryShapePage : public ILibraryPage
	{
	public:
		LibraryShapePage(wxWindow* parent);

		virtual bool isHandleSymbol(ISymbol* symbol) const;

	protected:
		virtual void onAddPress(wxCommandEvent& event);

	}; // LibraryShapePage
}

#endif // _WX_GUI_LIBRARY_SHAPE_PAGE_H_