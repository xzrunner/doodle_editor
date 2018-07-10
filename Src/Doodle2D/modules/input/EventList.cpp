#include "EventList.h"

using namespace d2d;

EventList::EventList()
{
}

EventList::~EventList()
{
	while (!empty())
		pop();
}

bool EventList::empty() const
{
	return m_events.empty();
}

void EventList::push(const Event& e)
{
	m_events.push(e);
}

Event EventList::pop()
{
	Event e = m_events.front();
	m_events.pop();
	return e;
}