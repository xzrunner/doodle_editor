#ifndef _FEDITOR_BASKETBALL_BLACKBOARD_H_
#define _FEDITOR_BASKETBALL_BLACKBOARD_H_
#include "../../AbstractBlackboard.h"

namespace FEDITOR
{
	namespace BASKETBALL
	{
		class Blackboard : public AbstractBlackboard
		{
		public:
			enum
			{
				e_OpenChains = EVENT_ID_BASE_PRIVATE_BLACKBOARD
			};

		public:

		}; // Blackboard
	}
}

#endif // _FEDITOR_BASKETBALL_BLACKBOARD_H_