#ifndef _EASY_BUILDER_SCENES_PAGE_H_
#define _EASY_BUILDER_SCENES_PAGE_H_

#include <wxGUI/wxGUI.h>

namespace ebuilder
{
	class ListObserver;
	class Behavior;

	class ScenesPage : public wxgui::ILibraryPage
	{
	public:
		ScenesPage(wxWindow* parent);
		virtual ~ScenesPage();

		virtual bool isHandleSymbol(wxgui::ISymbol* symbol) const;

		ListObserver* getListObserver() {
			return m_observer;
		}

		void refreshSceneThumbnail();

		void insertScene();

		void enableDelBtn();

	protected:
		virtual void initLayout(bool draggable = true);

		virtual void onAddPress(wxCommandEvent& event);
		virtual void onDelPress(wxCommandEvent& event);

	private:
		ListObserver* m_observer;

	}; // ScenesPage
}

#endif // _EASY_BUILDER_SCENES_PAGE_H_