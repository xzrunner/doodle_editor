#ifndef _FEDITOR_ABSTRACT_BLACKBOARD_H_
#define _FEDITOR_ABSTRACT_BLACKBOARD_H_
#include "Utility.h"

namespace FEDITOR
{
	class AbstractBlackboard
	{
	public:
		virtual ~AbstractBlackboard() {}

		bool hasNextEvent() const;
		Event getNextEvent();
		void pushEvent(Event event);

	private:
		std::queue<Event> m_eventList;

	}; // AbstractBlackboard

	inline bool AbstractBlackboard::hasNextEvent() const
	{
		return !m_eventList.empty();
	}

	inline Event AbstractBlackboard::getNextEvent()
	{
		if (hasNextEvent())
		{
			Event event = m_eventList.front();
			m_eventList.pop();
			return event;
		}
		else
		{
			return Event(-1);
		}
	}

	inline void AbstractBlackboard::pushEvent(Event event)
	{
		m_eventList.push(event);
	}
}

#endif // _FEDITOR_ABSTRACT_BLACKBOARD_H_