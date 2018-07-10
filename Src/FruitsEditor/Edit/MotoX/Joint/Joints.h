#ifndef _FEDITOR_MOTOX_JOINT_JOINTS_H_
#define _FEDITOR_MOTOX_JOINT_JOINTS_H_
#include "../ActorDefs.h"
#include <Fruits2D/Fruits2D.h>

class b2World;
class b2RevoluteJoint;
class b2WheelJoint;

namespace FEDITOR
{
	class Sprite;
	class ActorMotionAdapter;

	namespace MOTOX
	{
		namespace JOINT
		{
			class Parts;

			class Joints : public ISerializable
			{
			public:
				Joints(b2World* world, JointParams* jointParams);

				//
				// ISerializable interface
				//
				virtual void loadFromTextFile(std::ifstream& fin);
				virtual void storeToTextFile(std::ofstream& fout) const;

				void loadFromFileAdapter(const ActorMotionAdapter& adapter);

				void createJoint(size_t jointType, Parts& parts, const f2Vec2& anchor);
				void createWheelsJoint(Parts& parts);

				void setJointParams(size_t jointType);

				void setJointMotion(size_t jointType, bool isPositive);
				void setJointMotion(PLAYER_MOTION dir);

				const JointParams& getJointParams(size_t jointType) const;

			private:
				void initJointsParams();

				void createPlayerJoint(size_t jointID, size_t jointTypeID, 
					const Sprite* p0, const Sprite* p1, const f2Vec2& anchor);

				void doPlayerMotion(bool isLeftSide, bool turnRight); 

			private:
				static const float JOINTS_PARAMS[][6];
				static const bool JOINT_DIR_FLAG[][JOINTS_COUNT];

			private:
				class Joint
				{
				public:
					Joint();

					void setMotorSpeed(bool positive);

					void outputJointParams(std::ofstream& fout) const;

					void setJointLimitesType(bool isLeft);
					void resetParams();

				public:
					b2RevoluteJoint* m_joint;
					JointParams* m_params;

					bool m_useLeftLimites;

				}; // Joint

			private:
				b2World* m_world;
				JointParams* m_jointParams;

				Joint* m_joints[JOINTS_COUNT];
				b2WheelJoint *m_frontWheelJoint, *m_backWheelJoint;

				PLAYER_STATE m_state;

			}; // Joints
		}
	}
}

#endif // _FEDITOR_MOTOX_JOINT_JOINTS_H_