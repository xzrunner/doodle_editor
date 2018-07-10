#include "JointFactory.h"
#include "PhysicsJoint.h"
#include "PhysicsBody.h"

#include "common/math.h"

using namespace d2d;

b2Joint* JointFactory::createJoint(b2World* world, const PhysicsParser::Joint& data,
								   const std::vector<b2Body*>& bodies)
{
	b2Joint* pJoint = NULL;

	switch (data.type)
	{
	case PhysicsParser::Joint::e_revoluteJoint:
		{
			b2RevoluteJointDef jd;

			PhysicsParser::RevoluteJoint& sJoint 
				= static_cast<PhysicsParser::RevoluteJoint&>(const_cast<PhysicsParser::Joint&>(data));

			jd.Initialize(bodies[data.bodyA], bodies[data.bodyB], b2Vec2(0, 0));
			jd.collideConnected = sJoint.collideConnected;
			jd.localAnchorA.Set(sJoint.localAnchorA.x * BOX2D_SCALE_FACTOR_INVERSE, sJoint.localAnchorA.y * BOX2D_SCALE_FACTOR_INVERSE);
			jd.localAnchorB.Set(sJoint.localAnchorB.x * BOX2D_SCALE_FACTOR_INVERSE, sJoint.localAnchorB.y * BOX2D_SCALE_FACTOR_INVERSE);
			jd.referenceAngle = sJoint.referenceAngle;
			jd.enableLimit = sJoint.enableLimit;
			jd.lowerAngle = sJoint.lowerAngle;
			jd.upperAngle = sJoint.upperAngle;
			jd.enableMotor = sJoint.enableMotor;
			jd.maxMotorTorque = sJoint.maxMotorTorque;
			jd.motorSpeed = sJoint.motorSpeed;

			pJoint = world->CreateJoint(&jd);
		}
		break;
	case PhysicsParser::Joint::e_distanceJoint:
		{
			b2DistanceJointDef jd;

			PhysicsParser::DistanceJoint& sJoint
				= static_cast<PhysicsParser::DistanceJoint&>(const_cast<PhysicsParser::Joint&>(data));

			jd.bodyA = bodies[data.bodyA];
			jd.bodyB = bodies[data.bodyB];
			jd.collideConnected = sJoint.collideConnected;
			jd.localAnchorA.Set(sJoint.localAnchorA.x * BOX2D_SCALE_FACTOR_INVERSE, sJoint.localAnchorA.y * BOX2D_SCALE_FACTOR_INVERSE);
			jd.localAnchorB.Set(sJoint.localAnchorB.x * BOX2D_SCALE_FACTOR_INVERSE, sJoint.localAnchorB.y * BOX2D_SCALE_FACTOR_INVERSE);
			jd.length = sJoint.length * BOX2D_SCALE_FACTOR_INVERSE;
			jd.frequencyHz = sJoint.frequencyHz;
			jd.dampingRatio = sJoint.dampingRatio;

			pJoint = world->CreateJoint(&jd);
		}
		break;
	case PhysicsParser::Joint::e_wheelJoint:
		{
			b2WheelJointDef jd;

			PhysicsParser::WheelJoint& sJoint
				= static_cast<PhysicsParser::WheelJoint&>(const_cast<PhysicsParser::Joint&>(data));

			b2Vec2 anchor;
			anchor.x = sJoint.anchor.x * BOX2D_SCALE_FACTOR_INVERSE;
			anchor.y = sJoint.anchor.y * BOX2D_SCALE_FACTOR_INVERSE;

			jd.Initialize(bodies[data.bodyA], bodies[data.bodyB], anchor, 
				b2Vec2(sJoint.localAxisA.x, sJoint.localAxisA.y));
			jd.enableMotor = sJoint.enableMotor;
			jd.maxMotorTorque = sJoint.maxMotorTorque;
			jd.motorSpeed = sJoint.motorSpeed;
			jd.frequencyHz = sJoint.frequencyHz;
			jd.dampingRatio = sJoint.dampingRatio;

			pJoint = world->CreateJoint(&jd);
		}
		break;
	}

	return pJoint;
}
