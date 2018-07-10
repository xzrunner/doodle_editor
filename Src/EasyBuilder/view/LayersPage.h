#ifndef _EASY_BUILDER_LAYERS_PAGE_H_
#define _EASY_BUILDER_LAYERS_PAGE_H_

#include <wxGUI/wxGUI.h>

namespace ebuilder
{
	class LayersPage : public wxgui::ILibraryPage
	{
	public:
		LayersPage(wxWindow* parent);

		virtual bool isHandleSymbol(wxgui::ISymbol* symbol) const;

	protected:
		virtual void onAddPress(wxCommandEvent& event);

	}; // LayersPage
}

#endif // _EASY_BUILDER_LAYERS_PAGE_H_