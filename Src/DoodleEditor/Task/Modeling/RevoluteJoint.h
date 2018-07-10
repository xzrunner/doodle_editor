#ifndef _DEDITOR_MODELING_REVOLUTE_JOINT_H_
#define _DEDITOR_MODELING_REVOLUTE_JOINT_H_

#include "JointData.h"

namespace deditor
{
	namespace modeling
	{
		class RevoluteJoint : public JointData
		{
		public:
			RevoluteJoint(BodyData* b0, BodyData* b1);

			virtual bool isContain(const f2Vec2& pos) const;

			virtual void draw(DrawType type) const;

			f2Vec2 getWorldAnchorA() const;
			f2Vec2 getWorldAnchorB() const;

			void setLocalAnchorA(const f2Vec2& world);
			void setLocalAnchorB(const f2Vec2& world);

		private:
			void drawAnchor(const f2Vec2& pos, DrawType type) const;

		public:
			f2Vec2 localAnchorA;
			f2Vec2 localAnchorB;

			float referenceAngle;

			bool enableLimit;
			float lowerAngle;
			float upperAngle;

			bool enableMotor;
			float maxMotorTorque;

			float motorSpeed;

		}; // RevoluteJoint
	}
}

#endif // _DEDITOR_MODELING_REVOLUTE_JOINT_H_