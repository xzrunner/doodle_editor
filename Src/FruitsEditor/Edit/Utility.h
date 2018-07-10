#ifndef _FEDITOR_UTILITY_H_
#define _FEDITOR_UTILITY_H_
#include <Fruits2D/Fruits2D.h>

namespace FEDITOR
{
	static const int EVENT_ID_BASE_PRIVATE_BLACKBOARD	= 0;
	static const int EVENT_ID_BASE_PRIVATE_UI_CTRLS_MGR	= 200;
	static const int EVENT_ID_BASE_LAYERS_MGR_CMPT		= 400;

	static const float SCREEN_HEIGHT = 480.0f;
	static const float SCREEN_WIDTH = 800.0f;

	class Event
	{
	public:
		Event(int id) { m_id = id; }
		Event(int id, const std::string& info) 
			: m_info(info) { m_id = id; }

		int getID() const { return m_id; }

		const std::string& getInfo() const { 
			return m_info; 
		}

	private:
		int m_id;
		std::string m_info;

	}; // Event
}

#endif // _FEDITOR_UTILITY_H_