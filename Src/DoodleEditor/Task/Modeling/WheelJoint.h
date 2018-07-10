#ifndef _DEDITOR_MODELING_WHEEL_JOINT_H_
#define _DEDITOR_MODELING_WHEEL_JOINT_H_

#include "JointData.h"

namespace deditor
{
	namespace modeling
	{
		class WheelJoint : public JointData
		{
		public:
			WheelJoint(BodyData* b0, BodyData* b1);

			virtual bool isContain(const f2Vec2& pos) const;

			virtual void draw(DrawType type) const;

			f2Vec2 getWorldAnchorA() const;
			f2Vec2 getWorldAnchorB() const;

			void setLocalAnchorA(const f2Vec2& world);
			void setLocalAnchorB(const f2Vec2& world);

		private:
			void drawAxisALine(const f2Vec2& worldAnchorA) const;
			void drawFootBLine(const f2Vec2& worldAnchorA, const f2Vec2& worldAnchorB) const;

			void drawAnchorA(const f2Vec2& pos, DrawType type) const;
			void drawAnchorB(const f2Vec2& pos, DrawType type) const;

		public:
			f2Vec2 localAnchorA;
			f2Vec2 localAnchorB;

			f2Vec2 localAxisA;

			bool enableMotor;
			float maxMotorTorque;

			float motorSpeed;

			float frequencyHz;
			float dampingRatio;

		}; // WheelJoint
	}
}

#endif // _DEDITOR_MODELING_WHEEL_JOINT_H_