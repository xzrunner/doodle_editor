#ifndef _WX_GUI_LIBRARY_IMAGE_PAGE_H_
#define _WX_GUI_LIBRARY_IMAGE_PAGE_H_

#include "ILibraryPage.h"

namespace wxgui
{
	class LibraryImagePage : public ILibraryPage
	{
	public:
		LibraryImagePage(wxWindow* parent, bool supportBmp = true);

		virtual bool isHandleSymbol(ISymbol* symbol) const;

	protected:
		virtual void onAddPress(wxCommandEvent& event);

	private:
		bool m_supportBmp;

	}; // LibraryImagePage
}

#endif // _WX_GUI_LIBRARY_IMAGE_PAGE_H_