#ifndef _FEDITOR_COMPOSE_IMG_BLACKBOARD_H_
#define _FEDITOR_COMPOSE_IMG_BLACKBOARD_H_
#include "Edit/AbstractBlackboard.h"

namespace FEDITOR
{
	namespace COMPOSE_IMG
	{
		class Blackboard : public AbstractBlackboard
		{
		public:
			enum
			{
				e_OpenBackground = EVENT_ID_BASE_PRIVATE_BLACKBOARD,
				e_OpenTile,
				e_OpenLevel,
				e_SaveLevel
			};

		}; // Blackboard
	}
}

#endif // _FEDITOR_COMPOSE_IMG_BLACKBOARD_H_