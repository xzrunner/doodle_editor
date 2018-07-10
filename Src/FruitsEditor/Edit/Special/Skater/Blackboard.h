#ifndef _FEDITOR_SKATER_BLACKBOARD_H_
#define _FEDITOR_SKATER_BLACKBOARD_H_
#include "Edit/AbstractBlackboard.h"

namespace FEDITOR
{
	namespace SKATER
	{
		class Blackboard : public AbstractBlackboard
		{
		public:
			Blackboard();

			enum
			{
				e_OpenBackground = EVENT_ID_BASE_PRIVATE_BLACKBOARD,
				e_OpenTile,
				e_OpenLevel,
				e_OpenOldVersion,
				e_OpenBound,

				e_SaveLevel,
				e_SetTexCoords,
				e_SaveTrack
			};

		public:
			int m_gridType;
				// 0 none
				// 1 Y Bound
				// 2 XY Bound

			float m_texCoordLeft, m_texCoordRight,
				m_texCoordDown, m_texCoordUp;

		}; // Blackboard

		inline Blackboard::Blackboard()
		{
			m_gridType = 0;

			m_texCoordLeft = m_texCoordDown = 0.0f;
			m_texCoordRight = m_texCoordUp = 1.0f;
		}
	}
}

#endif // _FEDITOR_SKATER_BLACKBOARD_H_