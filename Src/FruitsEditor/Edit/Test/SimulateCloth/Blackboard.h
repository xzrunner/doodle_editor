#ifndef _FEDITOR_SIMULATE_CLOTH_BLACKBOARD_H_
#define _FEDITOR_SIMULATE_CLOTH_BLACKBOARD_H_
#include "Edit/AbstractBlackboard.h"

namespace FEDITOR
{
	namespace SIMULATE_CLOTH
	{
		class Blackboard : public AbstractBlackboard
		{
		public:
			Blackboard();

		public:
			enum
			{
				e_Step = EVENT_ID_BASE_PRIVATE_BLACKBOARD,

				e_openRegularTexture,
				e_openIrregularTexture,

				e_resetWeb,

// 				e_openLines,
// 				e_addStaticNode,
// 				e_addDynamicNode,
// 				e_buildWeb,

				e_resetJointsFrequency,
				e_resetJointsDamping,
				e_resetNodesEdge
			};

		public:
			// regular
			int m_row, m_col;
			int m_boundStatic;
			int m_connectNodeCenter;

			// params
			float m_frequencyHz, m_dampingRatio;
			float m_nodeHalfEdge;

		}; // Blackboard

		inline Blackboard::Blackboard()
		{
			m_row = m_col = 3;
			m_boundStatic = 1;
			m_connectNodeCenter = 1;

			m_frequencyHz = 2;
			m_dampingRatio = 0;
			m_nodeHalfEdge = 0.5f;
		}
	}
}

#endif // _FEDITOR_SIMULATE_CLOTH_BLACKBOARD_H_