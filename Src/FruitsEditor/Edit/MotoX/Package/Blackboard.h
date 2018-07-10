#ifndef _FEDITOR_MOTOX_PACKAGE_BLACKBOARD_H_
#define _FEDITOR_MOTOX_PACKAGE_BLACKBOARD_H_
#include "Edit/AbstractBlackboard.h"

namespace FEDITOR
{
	namespace MOTOX
	{
		namespace PACKAGE
		{
			class Blackboard : public AbstractBlackboard
			{
			public:
				enum
				{
					e_packTrackChains = EVENT_ID_BASE_PRIVATE_BLACKBOARD,
					e_packActor
				};

			}; // Blackboard
		}
	}
}

#endif // _FEDITOR_MOTOX_PACKAGE_BLACKBOARD_H_