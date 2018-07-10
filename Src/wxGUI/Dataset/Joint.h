#ifndef _WX_GUI_JOINT_H_
#define _WX_GUI_JOINT_H_

#include <Fruits2D/Fruits2D.h>

class b2Body;
class b2World;
class b2RevoluteJoint;

namespace wxgui
{
	struct JointDef;

	class Joint
	{
	public:
		Joint(b2World* world, const JointDef& params, const f2Vec2& anchor, 
			b2Body* b0, b2Body* b1, bool isMotor, float scale);
		~Joint();

		void setMotorSpeed(bool isPositive);
		void setAngleLimit(bool isLeft);

	private:
		void initialize(const JointDef& params, const f2Vec2& anchor, b2Body* b0, b2Body* b1, bool isMotor);

	private:
		float m_scale;

		b2World* m_world;
		b2RevoluteJoint* m_joint;

		float m_negativeSpeed, m_positiveSpeed;
		float m_leftAngleSmall, m_leftAngleLarge,
			m_rightAngleSmall, m_rightAngleLarge;

	}; // Joint
}

#endif // _WX_GUI_JOINT_H_