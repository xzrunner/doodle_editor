#ifndef _MOTOX_JOINT_H_
#define _MOTOX_JOINT_H_

#include <Doodle2D/doodle2d.h>
#include <Box2D/Box2D.h>

namespace motox
{
	struct JointDef
	{
		float positive_speed, negative_speed;
		float left_angle_small, left_angle_large,
			right_angle_small, right_angle_large;
		float max_torque;

		bool enableLimit, enableMotor;

	}; // JointDef

	class Joint
	{
	public:
		Joint(b2World* world, const JointDef& params, const d2d::Vector& anchor, 
			b2Body* b0, b2Body* b1, bool isMotor);
		~Joint();

		void setMotorSpeed(bool isPositive);
		void setAngleLimit(bool isLeft);

	private:
		b2World* m_world;
		b2RevoluteJoint* m_joint;

		JointDef m_params;

	}; // Joint
}

#endif // _MOTOX_JOINT_H_