#ifndef _FEDITOR_TEST_RENDERING_BLACKBOARD_H_
#define _FEDITOR_TEST_RENDERING_BLACKBOARD_H_
#include "Edit/AbstractBlackboard.h"

namespace FEDITOR
{
	namespace TEST_RENDERING
	{
		class Blackboard : public AbstractBlackboard
		{
		public:
			Blackboard();

			enum
			{
				e_Open = EVENT_ID_BASE_PRIVATE_BLACKBOARD,
				e_Step
			};

		public:
			int m_num;
			int m_renderType;
			int m_isTransparent;

		}; // Blackboard

		inline Blackboard::Blackboard()
		{
			m_num = 15000;
			m_renderType = 0;
			m_isTransparent = 1;
		}
	}
}

#endif // _FEDITOR_TEST_RENDERING_BLACKBOARD_H_