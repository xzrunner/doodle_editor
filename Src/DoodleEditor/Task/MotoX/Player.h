#ifndef _DEDITOR_MOTOX_PLAYER_H_
#define _DEDITOR_MOTOX_PLAYER_H_

#include "ActorDefs.h"
#include "LibraryActorItem.h"

#include <wxGUI/wxGUI.h>

namespace deditor
{
	namespace motox
	{
		class LibraryActorItem;
		struct DriveControl;
		struct ActorSettings;

		class Player
		{
		public:
			Player(b2World* world, wxgui::ISprite* motorbike);
			~Player();

			void loadParts(const LibraryActorItem& params);
			void loadJoints(const LibraryActorItem& params);
			void setCollisionFilter(const b2Filter& collision, const b2Filter& noCollision);

			void driving(const DriveControl& control, ActorSettings& settings);

		private:
			void clear();

			void createJoint(const LibraryActorItem::JointDef* joints, int jointID, int jointTypeID, 
 				int part0, int part1);
 			void createJointWithMotorbike(const LibraryActorItem::JointDef* joints, int jointID, 
 				int jointTypeID, int part);

			void doPlayerMotion(bool isLeftSide, bool turnRight);

		private:
			static const bool JOINT_DIR_FLAG[][JOINTS_COUNT];

		private:
			b2World* m_world;

			wxgui::ISprite* m_motorbike;

			wxgui::ISprite* m_parts[PLAYER_PARTS_COUNT];
			wxgui::Joint* m_joints[JOINTS_COUNT];

			PLAYER_STATE m_state;

			bool m_bActive;

			friend class Actor;

		}; // Player
	}
}

#endif // _DEDITOR_MOTOX_PLAYER_H_