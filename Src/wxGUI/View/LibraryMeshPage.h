#ifndef _WX_GUI_LIBRARY_MESH_PAGE_H_
#define _WX_GUI_LIBRARY_MESH_PAGE_H_

#include "ILibraryPage.h"

namespace wxgui
{
	class LibraryMeshPage : public ILibraryPage
	{
	public:
		LibraryMeshPage(wxWindow* parent);

		virtual bool isHandleSymbol(ISymbol* symbol) const;

	protected:
		virtual void onAddPress(wxCommandEvent& event);

	}; // LibraryMeshPage
}

#endif // _WX_GUI_LIBRARY_MESH_PAGE_H_