#ifndef _D2D_EVENT_LIST_H_
#define _D2D_EVENT_LIST_H_

#include "common/Vector.h"

#include <queue>

namespace d2d
{
	enum EventType
	{
		e_touch_down,
		e_touch_up,
		e_touch_move,

		e_key_down,
		e_key_up,
		e_key_back_down,
		e_key_menu_down
	};

	struct Event
	{
		EventType type;
		Vector pos;

		Event(EventType t, const Vector& p) : type(t), pos(p) {}
	};

	class EventList
	{
	public:
		EventList();
		virtual ~EventList();

		bool empty() const;

		void push(const Event& e);
		Event pop();

	private:
		std::queue<Event> m_events;

	}; // EventList
}

#endif // _D2D_EVENT_LIST_H_