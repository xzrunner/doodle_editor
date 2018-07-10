#ifndef _FEDITOR_MONSTER_BLACKBOARD_H_
#define _FEDITOR_MONSTER_BLACKBOARD_H_
#include "Edit/AbstractBlackboard.h"

namespace FEDITOR
{
	namespace MONSTER
	{
		class Blackboard : public AbstractBlackboard
		{
		public:
			Blackboard();

		public:
			enum
			{
				e_openTile = EVENT_ID_BASE_PRIVATE_BLACKBOARD,
				e_openLevel,
				e_saveLevel,
				e_resizeBg,
				e_Play
			};

			static const int ROW = 4;
			static const int COL = 7;

		public:
			int m_edge;
			int m_length;
			int m_time;

			int m_minEmptyGrid, m_maxEmptyGrid;

		}; // Blackboard

		inline Blackboard::Blackboard()
		{
			m_edge = 60;
			m_length = 50;
			m_time = 60;

			m_minEmptyGrid = m_maxEmptyGrid = 0;
		}
	}
}

#endif // _FEDITOR_MONSTER_BLACKBOARD_H_