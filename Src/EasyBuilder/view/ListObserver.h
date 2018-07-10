#ifndef _EASY_BUILDER_LIST_OBSERVER_H_
#define _EASY_BUILDER_LIST_OBSERVER_H_

#include <wxGUI/wxGUI.h>

namespace ebuilder
{
	class Behavior;
	class BehaviorPanel;

	class ListObserver
	{
	public:
		ListObserver(wxgui::LibraryList* list);
		
		void registerListener(Behavior* lsn);
		void registerListener(BehaviorPanel* lsn);

		void removeListener(Behavior* lsn);
		void clearUIListeners();

		void updateListeners();

	private:
		wxgui::LibraryList* m_list;

		std::vector<Behavior*> m_listeners;
		std::vector<BehaviorPanel*> m_uiListeners;

	}; // ListObserver
}

#endif // _EASY_BUILDER_LIST_OBSERVER_H_