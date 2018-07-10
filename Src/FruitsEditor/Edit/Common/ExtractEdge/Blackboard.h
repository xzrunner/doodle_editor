#ifndef _FEDITOR_EXTRACT_EDGE_BLACKBOARD_H_
#define _FEDITOR_EXTRACT_EDGE_BLACKBOARD_H_
#include "Edit/AbstractBlackboard.h"

namespace FEDITOR
{
	namespace EXTRACT_EDGE
	{
		class Blackboard : public AbstractBlackboard
		{
		public:
			Blackboard();

		public:
			enum
			{
				e_OpenFile = EVENT_ID_BASE_PRIVATE_BLACKBOARD,

				e_SetCoordLinesVisible,
				e_ChangeCoordLines,

				e_SavePolyline,

				e_SetColorTol,
				e_SetEdgeTol,
				e_AutoSelect
			};

		public:
			int m_drawCoordLines;
			
			// 0-center; 1-left_low; 2-left_top
			int m_coordsType;

			int m_colorTolerance;
			float m_edgeTolerance;

		}; // Blackboard

		inline Blackboard::Blackboard()
		{
			m_drawCoordLines = 1;
			m_coordsType = 0;
		}
	}
}

#endif // _FEDITOR_EXTRACT_EDGE_BLACKBOARD_H_