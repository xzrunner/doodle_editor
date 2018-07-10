#ifndef _EASY_BUILDER_MEDIA_PAGE_H_
#define _EASY_BUILDER_MEDIA_PAGE_H_

#include <wxGUI/wxGUI.h>

namespace ebuilder
{
	class ListObserver;
	class Behavior;

	class MediaPage : public wxgui::ILibraryPage
	{
	public:
		MediaPage(wxWindow* parent);
		virtual ~MediaPage();

		virtual bool isHandleSymbol(wxgui::ISymbol* symbol) const;

		ListObserver* getListObserver() {
			return m_observer;
		}

	protected:
		virtual void onAddPress(wxCommandEvent& event);
		virtual void onDelPress(wxCommandEvent& event);

	private:
		ListObserver* m_observer;

	}; // MediaPage
}

#endif // _EASY_BUILDER_MEDIA_PAGE_H_