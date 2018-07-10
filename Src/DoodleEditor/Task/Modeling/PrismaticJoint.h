#ifndef _DEDITOR_MODELING_PRISMATIC_JOINT_H_
#define _DEDITOR_MODELING_PRISMATIC_JOINT_H_

#include "JointData.h"

namespace deditor
{
	namespace modeling
	{
		class PrismaticJoint : public JointData
		{
		public:
			PrismaticJoint(BodyData* b0, BodyData* b1);

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

			f2Vec2 localAxisA;

			float referenceAngle;

			bool enableLimit;
			float lowerTranslation;
			float upperTranslation;

			bool enableMotor;
			float maxMotorForce;

			float motorSpeed;

		}; // PrismaticJoint
	}
}

#endif // _DEDITOR_MODELING_PRISMATIC_JOINT_H_