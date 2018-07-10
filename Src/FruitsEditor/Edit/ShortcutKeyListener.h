#ifndef _FEDITOR_SHORTCUT_KEY_LISTENER_H_
#define _FEDITOR_SHORTCUT_KEY_LISTENER_H_
#include "Utility.h"

namespace FEDITOR
{
	class ShortcutKeyListener
	{
	public:
		ShortcutKeyListener();

		void registerEventList(std::queue<Event>* eventList);

		void registerKeyEvent(unsigned char key, int eventID);

		void onKeyboard(unsigned char key) const;

	private:
		int queryEventByKey(unsigned char key) const;

	private:
		std::map<unsigned char, int> m_mapKeyToID;

		std::queue<Event>* m_eventList;

	}; // ShortcutKeyListener

	inline ShortcutKeyListener::ShortcutKeyListener()
	{
		m_eventList = NULL;
	}

	inline void ShortcutKeyListener::registerEventList(std::queue<Event>* eventList)
	{
		m_eventList = eventList;
	}

	inline void ShortcutKeyListener::registerKeyEvent(unsigned char key, int eventID)
	{
		m_mapKeyToID.insert(std::make_pair(tolower(key), eventID));
	}

	inline void ShortcutKeyListener::onKeyboard(unsigned char key) const
	{
		if (!m_eventList) return;

		int id = queryEventByKey(tolower(key));
		if (id != -1) m_eventList->push(Event(id));
	}

	inline int ShortcutKeyListener::queryEventByKey(unsigned char key) const
	{
		std::map<unsigned char, int>::const_iterator itr = m_mapKeyToID.find(key);
		if (itr == m_mapKeyToID.end()) return -1;
		else return itr->second;
	}
}

#endif // _FEDITOR_SHORTCUT_KEY_LISTENER_H_