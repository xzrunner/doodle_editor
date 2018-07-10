#ifndef _FEDITOR_FILL_COLOR_BLACKBOARD_H_
#define _FEDITOR_FILL_COLOR_BLACKBOARD_H_
#include "Edit/AbstractBlackboard.h"

namespace FEDITOR
{
	namespace FILL_COLOR
	{
		class Blackboard : public AbstractBlackboard
		{
		public:
			Blackboard();

			enum
			{
				e_OpenChains = EVENT_ID_BASE_PRIVATE_BLACKBOARD,
				e_OpenTris,
				e_OpenImg,
				e_OpenFill,
				e_SaveTris,
				e_SaveFill,
				e_SetColor,
				e_ChangeSelectFlag
			};

		public:
			f2Colorf m_color;

			int m_flagSelectCtlpos;

		}; // Blackboard

		inline Blackboard::Blackboard()
		{
			m_flagSelectCtlpos = 0;
		}
	}
}

#endif // _FEDITOR_FILL_COLOR_BLACKBOARD_H_