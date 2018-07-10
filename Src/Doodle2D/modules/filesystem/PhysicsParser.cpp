#include "PhysicsParser.h"

#include "common/tools.h"

using namespace d2d;

PhysicsParser::Body::~Body()
{
	for_each(fixtures.begin(), fixtures.end(), DeletePointerFunctor<Fixture>());
	fixtures.clear();
}

PhysicsParser::~PhysicsParser()
{
	clear();
}

void PhysicsParser::parser(byte*& ptr)
{
	clear();

	parserBodies(ptr);
	parserJoints(ptr);
}

void PhysicsParser::clear()
{
	for_each(bodies.begin(), bodies.end(), DeletePointerFunctor<Body>());
	bodies.clear();

	for_each(joints.begin(), joints.end(), DeletePointerFunctor<Joint>());
	joints.clear();
}

void PhysicsParser::parserBodies(byte*& ptr)
{
	size_t size = 0;
	memcpy(&size, ptr, sizeof(size_t));
	ptr += sizeof(size_t);
	bodies.reserve(size);
	for (size_t i = 0; i < size; ++i)
		bodies.push_back(parserBody(ptr));
}

PhysicsParser::Body* PhysicsParser::parserBody(byte*& ptr)
{
	Body* body = new Body;

	memcpy(&body->type, ptr, sizeof(size_t));
	ptr += sizeof(int);

	memcpy(&body->location.x, ptr, sizeof(float));
	ptr += sizeof(float);
	memcpy(&body->location.y, ptr, sizeof(float));
	ptr += sizeof(float);
	memcpy(&body->angle, ptr, sizeof(float));
	ptr += sizeof(float);

	size_t size = 0;
	memcpy(&size, ptr, sizeof(size_t));
	ptr += sizeof(size_t);
	body->fixtures.reserve(size);
	for (size_t i = 0; i < size; ++i)
		body->fixtures.push_back(parserFixture(ptr));

	return body;
}

PhysicsParser::Fixture* PhysicsParser::parserFixture(byte*& ptr)
{
	Fixture* fixture = new Fixture;

	memcpy(&fixture->density, ptr, sizeof(float));
	ptr += sizeof(float);
	memcpy(&fixture->friction, ptr, sizeof(float));
	ptr += sizeof(float);
	memcpy(&fixture->restitution, ptr, sizeof(float));
	ptr += sizeof(float);

	Shape::Type type;
	memcpy(&type, ptr, sizeof(int));
	ptr += sizeof(int);
	switch (type)
	{
	case Shape::e_circle:
		{
			CircleShape* circle = new CircleShape;

			memcpy(&circle->radius, ptr, sizeof(float));
			ptr += sizeof(float);
			memcpy(&circle->center.x, ptr, sizeof(float));
			ptr += sizeof(float);
			memcpy(&circle->center.y, ptr, sizeof(float));
			ptr += sizeof(float);

			fixture->shape = circle;
		}
		break;
	case Shape::e_polygon:
		{
			PolygonShape* poly = new PolygonShape;

			size_t size;
			memcpy(&size, ptr, sizeof(size_t));
			ptr += sizeof(size_t);
			poly->vertices.reserve(size);
			for (size_t i = 0; i < size; ++i)
			{
				Vector pos;
				memcpy(&pos.x, ptr, sizeof(float));
				ptr += sizeof(float);
				memcpy(&pos.y, ptr, sizeof(float));
				ptr += sizeof(float);
				poly->vertices.push_back(pos);
			}

			fixture->shape = poly;
		}
		break;
	}
	fixture->shape->type = type;

	return fixture;
}

void PhysicsParser::parserJoints(byte*& ptr)
{
	size_t size = 0;
	memcpy(&size, ptr, sizeof(size_t));
	ptr += sizeof(size_t);

	joints.reserve(size);
	for (size_t i = 0; i < size; ++i)
		joints.push_back(parserJoint(ptr));
}

PhysicsParser::Joint* PhysicsParser::parserJoint(byte*& ptr)
{
	Joint* joint = NULL;

	Joint::Type type;
	memcpy(&type, ptr, sizeof(int));
	ptr += sizeof(int);
	switch (type)
	{
	case Joint::e_revoluteJoint:
		{
			RevoluteJoint* rJoint = new RevoluteJoint;

			parserJointCommon(rJoint, ptr);

			memcpy(&rJoint->localAnchorA.x, ptr, sizeof(float));
			ptr += sizeof(float);
			memcpy(&rJoint->localAnchorA.y, ptr, sizeof(float));
			ptr += sizeof(float);
			memcpy(&rJoint->localAnchorB.x, ptr, sizeof(float));
			ptr += sizeof(float);
			memcpy(&rJoint->localAnchorB.y, ptr, sizeof(float));
			ptr += sizeof(float);

			memcpy(&rJoint->referenceAngle, ptr, sizeof(float));
			ptr += sizeof(float);

			memcpy(&rJoint->enableLimit, ptr, sizeof(int));
			ptr += sizeof(int);
			memcpy(&rJoint->lowerAngle, ptr, sizeof(float));
			ptr += sizeof(float);
			memcpy(&rJoint->upperAngle, ptr, sizeof(float));
			ptr += sizeof(float);

			memcpy(&rJoint->enableMotor, ptr, sizeof(int));
			ptr += sizeof(int);
			memcpy(&rJoint->maxMotorTorque, ptr, sizeof(float));
			ptr += sizeof(float);

			memcpy(&rJoint->motorSpeed, ptr, sizeof(float));
			ptr += sizeof(float);

			joint = rJoint;
		}
		break;
	case Joint::e_prismaticJoint:
		{
			PrismaticJoint* pJoint = new PrismaticJoint;

			parserJointCommon(pJoint, ptr);

			memcpy(&pJoint->localAnchorA.x, ptr, sizeof(float));
			ptr += sizeof(float);
			memcpy(&pJoint->localAnchorA.y, ptr, sizeof(float));
			ptr += sizeof(float);
			memcpy(&pJoint->localAnchorB.x, ptr, sizeof(float));
			ptr += sizeof(float);
			memcpy(&pJoint->localAnchorB.y, ptr, sizeof(float));
			ptr += sizeof(float);

			memcpy(&pJoint->localAxisA.x, ptr, sizeof(float));
			ptr += sizeof(float);
			memcpy(&pJoint->localAxisA.y, ptr, sizeof(float));
			ptr += sizeof(float);

			memcpy(&pJoint->referenceAngle, ptr, sizeof(float));
			ptr += sizeof(float);

			memcpy(&pJoint->enableLimit, ptr, sizeof(int));
			ptr += sizeof(int);
			memcpy(&pJoint->lowerTranslation, ptr, sizeof(float));
			ptr += sizeof(float);
			memcpy(&pJoint->upperTranslation, ptr, sizeof(float));
			ptr += sizeof(float);

			memcpy(&pJoint->enableMotor, ptr, sizeof(int));
			ptr += sizeof(int);
			memcpy(&pJoint->maxMotorForce, ptr, sizeof(float));
			ptr += sizeof(float);

			memcpy(&pJoint->motorSpeed, ptr, sizeof(float));
			ptr += sizeof(float);

			joint = pJoint;
		}
		break;
	case Joint::e_distanceJoint:
		{
			DistanceJoint* dJoint = new DistanceJoint;

			parserJointCommon(dJoint, ptr);

			memcpy(&dJoint->localAnchorA.x, ptr, sizeof(float));
			ptr += sizeof(float);
			memcpy(&dJoint->localAnchorA.y, ptr, sizeof(float));
			ptr += sizeof(float);
			memcpy(&dJoint->localAnchorB.x, ptr, sizeof(float));
			ptr += sizeof(float);
			memcpy(&dJoint->localAnchorB.y, ptr, sizeof(float));
			ptr += sizeof(float);

			memcpy(&dJoint->length, ptr, sizeof(float));
			ptr += sizeof(float);

			memcpy(&dJoint->frequencyHz, ptr, sizeof(float));
			ptr += sizeof(float);
			memcpy(&dJoint->dampingRatio, ptr, sizeof(float));
			ptr += sizeof(float);

			joint = dJoint;
		}
		break;
	case Joint::e_wheelJoint:
		{
			WheelJoint* wJoint = new WheelJoint;

			parserJointCommon(wJoint, ptr);

			memcpy(&wJoint->anchor.x, ptr, sizeof(float));
			ptr += sizeof(float);
			memcpy(&wJoint->anchor.y, ptr, sizeof(float));
			ptr += sizeof(float);

			memcpy(&wJoint->localAxisA.x, ptr, sizeof(float));
			ptr += sizeof(float);
			memcpy(&wJoint->localAxisA.y, ptr, sizeof(float));
			ptr += sizeof(float);

			memcpy(&wJoint->enableMotor, ptr, sizeof(int));
			ptr += sizeof(int);
			memcpy(&wJoint->maxMotorTorque, ptr, sizeof(float));
			ptr += sizeof(float);

			memcpy(&wJoint->motorSpeed, ptr, sizeof(float));
			ptr += sizeof(float);

			memcpy(&wJoint->frequencyHz, ptr, sizeof(float));
			ptr += sizeof(float);
			memcpy(&wJoint->dampingRatio, ptr, sizeof(float));
			ptr += sizeof(float);

			joint = wJoint;
		}
		break;
	}

	joint->type = type;

	return joint;
}

void PhysicsParser::parserJointCommon(Joint* joint, byte*& ptr)
{
	size_t bodyA = 0;
	memcpy(&bodyA, ptr, sizeof(size_t));
	ptr += sizeof(size_t);
	size_t bodyB = 0;
	memcpy(&bodyB, ptr, sizeof(size_t));
	ptr += sizeof(size_t);
	joint->bodyA = bodyA;
	joint->bodyB = bodyB;

	memcpy(&joint->collideConnected, ptr, sizeof(int));
	ptr += sizeof(int);
}