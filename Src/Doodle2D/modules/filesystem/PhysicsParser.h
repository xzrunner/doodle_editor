#ifndef _D2D_PHYSICS_PARSER_H_
#define _D2D_PHYSICS_PARSER_H_

#include "Common/types.h"
#include "Common/Vector.h"

#include <vector>

namespace d2d
{
	class PhysicsParser
	{
	public:
		struct Shape
		{
			enum Type
			{
				e_circle = 0,
				e_polygon
			};

			Type type;

		}; // Shape

		struct CircleShape : public Shape
		{
			Vector center;
			float radius;

		}; // CircleShape

		struct PolygonShape : public Shape
		{
			std::vector<Vector> vertices;

		}; // PolygonShape

		struct Fixture
		{
			Shape* shape;

			float density;

			float friction;
			float restitution;

			bool isSensor;

			unsigned short categoryBits;
			unsigned short maskBits;
			short groupIndex;

		}; // Fixture

		struct Body
		{
			enum Type
			{
				e_static = 0,
				e_kinematic,
				e_dynamic
			};

			Type type;

			Vector location;
			float angle;

			std::vector<Fixture*> fixtures;

			~Body();

		}; // Body

		struct Joint
		{
			enum Type
			{
				e_revoluteJoint,
				e_prismaticJoint,
				e_distanceJoint,
				e_pulleyJoint,
				e_mouseJoint,
				e_gearJoint,
				e_wheelJoint,
				e_weldJoint,
				e_frictionJoint,
				e_ropeJoint
			};

			Type type;

			size_t bodyA;
			size_t bodyB;

			bool collideConnected;

		}; // Joint

		struct RevoluteJoint : public Joint
		{
			Vector localAnchorA;
			Vector localAnchorB;

			float referenceAngle;

			bool enableLimit;
			float lowerAngle;
			float upperAngle;

			bool enableMotor;
			float maxMotorTorque;

			float motorSpeed;

		}; // RevoluteJoint

		struct PrismaticJoint : public Joint
		{
			Vector localAnchorA;
			Vector localAnchorB;

			Vector localAxisA;

			float referenceAngle;

			bool enableLimit;
			float lowerTranslation;
			float upperTranslation;

			bool enableMotor;
			float maxMotorForce;

			float motorSpeed;

		}; // PrismaticJoint

		struct DistanceJoint : public Joint
		{
			Vector localAnchorA;
			Vector localAnchorB;

			float length;

			float frequencyHz;
			float dampingRatio;

		}; // DistanceJoint

		struct WheelJoint : public Joint
		{
			Vector anchor;

			Vector localAxisA;

			bool enableMotor;
			float maxMotorTorque;

			float motorSpeed;

			float frequencyHz;
			float dampingRatio;

		}; // WheelJoint

	public:
		~PhysicsParser();
		
		void parser(byte*& ptr);

	private:
		void clear();

		void parserBodies(byte*& ptr);
		Body* parserBody(byte*& ptr);
		Fixture* parserFixture(byte*& ptr);

		void parserJoints(byte*& ptr);
		Joint* parserJoint(byte*& ptr);
		void parserJointCommon(Joint* joint, byte*& ptr);

	public:
		std::vector<Body*> bodies;
		std::vector<Joint*> joints;

	}; // PhysicsParser
}

#endif // _D2D_PHYSICS_PARSER_H_