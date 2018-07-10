#ifndef _FEDITOR_CHESSBOARD_BLACKBOARD_H_
#define _FEDITOR_CHESSBOARD_BLACKBOARD_H_
#include "Edit/AbstractBlackboard.h"

namespace FEDITOR
{
	namespace CHESSBOARD
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
				e_resizeBg
			};

		public:
			int m_col, m_row;
			int m_edge;

		}; // Blackboard

		inline Blackboard::Blackboard()
		{
			m_col = 7;
			m_row = 30;

			m_edge = 60;
		}
	}
}

#endif // _FEDITOR_CHESSBOARD_BLACKBOARD_H_