#ifndef _DEDITOR_MOTOX_ACTOR_EDIT_JOINTS_H_
#define _DEDITOR_MOTOX_ACTOR_EDIT_JOINTS_H_

#include "LibraryActorItem.h"

#include <Box2D/Box2D.h>

namespace deditor
{
	namespace motox
	{
		class LibraryActorItem;
		class AEParts;

		class AEJoints
		{
		public:
			AEJoints(b2World* world, LibraryActorItem& params, AEParts& parts);

			void initFromParams();

			void createJoint(size_t jointType, const f2Vec2& anchor);
			void createWheelsJoint();
			void createAllJoints();

			void setJointParams(size_t jointType);

			void setJointMotion(size_t jointType, bool isPositive);
			void setJointMotion(PLAYER_MOTION dir);

			const LibraryActorItem::JointDef& getJointParams(size_t jointType) const;

			void onDraw() const;

			void clear();

		private:
			void loadFromParams();

			void createPlayerJoint(size_t jointID, size_t jointTypeID, 
				const wxgui::ISprite* p0, const wxgui::ISprite* p1, const f2Vec2& anchor);

			void doPlayerMotion(bool isLeftSide, bool turnRight); 

		private:
			static const float JOINTS_PARAMS[][7];
			static const bool JOINT_DIR_FLAG[][JOINTS_COUNT];

		private:
			class Joint
			{
			public:
				Joint();

				void setMotorSpeed(bool positive);

				void setJointLimites(bool isLeft);
				void resetParams();

			private:
				b2RevoluteJoint* m_joint;
				wxgui::JointDef* m_params;

				bool m_useLeftLimites;

				friend class AEJoints;

			}; // Joint

		private:
			b2World* m_world;

			LibraryActorItem& m_params;

			AEParts& m_parts;

			Joint* m_joints[JOINTS_COUNT];
			b2WheelJoint *m_frontWheelJoint, *m_backWheelJoint;

			PLAYER_STATE m_state;

			friend class AEParamsCMPT;

		}; // AEJoints
	}
}

#endif // _DEDITOR_MOTOX_ACTOR_EDIT_JOINTS_H_
