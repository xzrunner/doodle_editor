#ifndef _EASY_BUILDER_ACTORS_PAGE_H_
#define _EASY_BUILDER_ACTORS_PAGE_H_

#include <wxGUI/wxGUI.h>

namespace ebuilder
{
	class ActorsPage : public wxgui::ILibraryPage
	{
	public:
		ActorsPage(wxWindow* parent);

		//
		// wxgui::ILibraryPage interface
		//
		virtual bool isHandleSymbol(wxgui::ISymbol* symbol) const;

	protected:
		virtual void initLayout(bool draggable = true);

		virtual void onAddPress(wxCommandEvent& event);

	protected:
		void initButtons(wxSizer* sizer);

	}; // ActorsPage
}

#endif // _EASY_BUILDER_ACTORS_PAGE_H_