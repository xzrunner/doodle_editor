#ifndef _MOTOX_PLAYER_H_
#define _MOTOX_PLAYER_H_

#include "ActorDefs.h"

#include "Tools/Sprite.h"
#include "Tools/Joint.h"

#include <Box2D/Box2D.h>

namespace motox
{
	struct DriveControl;
	struct ActorSettings;

	class Player
	{
	public:
		Player(b2World* world);
		~Player();

		void update();

		void driving(const DriveControl& control, ActorSettings& settings);

	private:
		void clear();

		void doPlayerMotion(bool isLeftSide, bool turnRight);

	private:
		static const bool JOINT_DIR_FLAG[][JOINTS_COUNT];

	private:
		b2World* m_world;

		Sprite* m_motorbike;

		Sprite* m_parts[PLAYER_PARTS_COUNT];
		Joint* m_joints[JOINTS_COUNT];

		PLAYER_STATE m_state;

		friend class Actor;
		friend class ActorLoaderNew;

	}; // Player
}

#endif // _MOTOX_PLAYER_H_