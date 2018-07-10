#ifndef _FEDITOR_ABSTRACT_MODEL_H_
#define _FEDITOR_ABSTRACT_MODEL_H_
#include "Utility.h"

namespace FEDITOR
{
	class LayersMgr;

	class AbstractModel
	{
	public:
		AbstractModel();
		virtual ~AbstractModel();

		virtual void handleEvent(const Event& event) = 0;

		const LayersMgr& getLayersMgrConst() const;
		LayersMgr& getLayersMgr();

		bool hasNextEvent() const;
		Event getNextEvent();
		void pushEvent(Event event);

	protected:
		LayersMgr* m_layers;

		std::queue<Event> m_eventList;

	}; // AbstractModel

	inline const LayersMgr& AbstractModel::getLayersMgrConst() const
	{
		return *m_layers;
	}

	inline LayersMgr& AbstractModel::getLayersMgr()
	{
		return *m_layers;
	}

	inline bool AbstractModel::hasNextEvent() const
	{
		return !m_eventList.empty();
	}

	inline Event AbstractModel::getNextEvent()
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

	inline void AbstractModel::pushEvent(Event event)
	{
		m_eventList.push(event);
	}
}

#endif // _FEDITOR_ABSTRACT_MODEL_H_