#ifndef _FEDITOR_MOTOX_PLAYER_H_
#define _FEDITOR_MOTOX_PLAYER_H_
#include <Fruits2D/Fruits2D.h>
#include "ActorDefs.h"

class b2World;
struct b2Filter;

namespace FEDITOR
{
	class Joint;
	class Sprite;
	class Layer;
	class ActorMotionAdapter;

	namespace MOTOX
	{
		struct DriveControl;
		struct ActorSettings;

		class Player
		{
		public:
			Player(b2World* world, Layer* layer, Sprite* motorbike);
			~Player();

			void loadFromAdapterFile(const ActorMotionAdapter& adapter);
			void setCollisionFilter(const b2Filter& collision, const b2Filter& noCollision);

			void driving(const DriveControl& control, ActorSettings& settings);

		private:
			void clear();

			void loadPartsFromAdapterFile(const ActorMotionAdapter& adapter);
			void loadJointsFromAdapterFile(const ActorMotionAdapter& adapter);

			void doPlayerMotion(bool isLeftSide, bool turnRight);

		private:
			static const bool JOINT_DIR_FLAG[][JOINTS_COUNT];

		private:
			b2World* m_world;
			Layer* m_layer;
			Sprite* m_motorbike;

			Sprite* m_parts[PLAYER_PARTS_COUNT];
			Joint* m_joints[JOINTS_COUNT];
			
			PLAYER_STATE m_state;

			friend class Actor;

		}; // Player
	}
}

#endif // _FEDITOR_MOTOX_PLAYER_H_