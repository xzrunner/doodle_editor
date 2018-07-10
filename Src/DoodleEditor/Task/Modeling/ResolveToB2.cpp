#include "ResolveToB2.h"
#include "BodyData.h"
#include "FixtureData.h"
#include "RevoluteJoint.h"
#include "PrismaticJoint.h"
#include "DistanceJoint.h"
#include "WheelJoint.h"
#include "Shape.h"

using namespace deditor::modeling;

b2Body* ResolveToB2::createBody(const BodyData& data, b2World* world,
								std::map<BodyData*, b2Body*>& bodyMap)
{
	b2BodyDef bd;
	switch (data.m_type)
	{
	case BodyData::e_static:
		bd.type = b2_staticBody;
		break;
	case BodyData::e_kinematic:
		bd.type = b2_kinematicBody;
		break;
	case BodyData::e_dynamic:
		bd.type = b2_dynamicBody;
		break;
	}
	bd.gravityScale = data.m_gravityScale;
	b2Body* body = world->CreateBody(&bd);
	bodyMap.insert(std::make_pair(const_cast<BodyData*>(&data), body));

	b2Vec2 pos;
	pos.x = data.m_sprite->getPosition().x / BOX2D_SCALE_FACTOR;
	pos.y = data.m_sprite->getPosition().y / BOX2D_SCALE_FACTOR;
	body->SetTransform(pos, data.m_sprite->getAngle());

	for (size_t i = 0, n = data.m_fixtures.size(); i < n; ++i)
	{
		FixtureData* fData = data.m_fixtures[i];

		b2FixtureDef fd;
		fd.density = fData->density;
		fd.friction = fData->friction;
		fd.restitution = fData->restitution;
		fd.isSensor = fData->isSensor;
		fd.filter.categoryBits = fData->categoryBits;
		fd.filter.maskBits = fData->maskBits;
		fd.filter.groupIndex = fData->groupIndex;

		switch(fData->shape->getType())
		{
		case IShape::e_circle:
			{
				CircleShape* circle = static_cast<CircleShape*>(fData->shape);
				b2CircleShape shape;
				shape.m_radius = circle->m_radius / BOX2D_SCALE_FACTOR;
				shape.m_p.x = circle->m_center.x / BOX2D_SCALE_FACTOR;
				shape.m_p.y = circle->m_center.y / BOX2D_SCALE_FACTOR;

				fd.shape = &shape;
				body->CreateFixture(&fd);
			}
			break;
		case IShape::e_polygon:
			{
				PolygonShape* poly = static_cast<PolygonShape*>(fData->shape);
				const size_t size = poly->m_vertices.size();
				std::vector<b2Vec2> vertices(size);
				for (size_t j = 0; j < size; ++j)
				{
					vertices[j].x = poly->m_vertices[j].x / BOX2D_SCALE_FACTOR;
					vertices[j].y = poly->m_vertices[j].y / BOX2D_SCALE_FACTOR;
				}

				b2PolygonShape shape;
				shape.Set(&vertices[0], size);

				fd.shape = &shape;
				body->CreateFixture(&fd);
			}
			break;
		}
	}

	return body;
}

b2Joint* ResolveToB2::createJoint(const JointData& data, b2World* world,
								  const std::map<BodyData*, b2Body*>& bodyMap)
{
	b2Joint* bJoint = NULL;

	switch(data.type)
	{
	case JointData::e_revoluteJoint:
		{
			b2RevoluteJointDef jd;

			RevoluteJoint* joint = static_cast<RevoluteJoint*>(const_cast<JointData*>(&data));

			std::map<BodyData*, b2Body*>::const_iterator 
				itrA = bodyMap.find(joint->bodyA),
				itrB = bodyMap.find(joint->bodyB);
			assert(itrA != bodyMap.end() && itrB != bodyMap.end());
			b2Body* bodyA = itrA->second;
			b2Body* bodyB = itrB->second;
			jd.Initialize(bodyA, bodyB, b2Vec2(0, 0));
			jd.collideConnected = joint->collideConnected;
			jd.localAnchorA.Set(joint->localAnchorA.x / BOX2D_SCALE_FACTOR, joint->localAnchorA.y / BOX2D_SCALE_FACTOR);
			jd.localAnchorB.Set(joint->localAnchorB.x / BOX2D_SCALE_FACTOR, joint->localAnchorB.y / BOX2D_SCALE_FACTOR);
			jd.referenceAngle = joint->referenceAngle;
			jd.enableLimit = joint->enableLimit;
			jd.lowerAngle = joint->lowerAngle;
			jd.upperAngle = joint->upperAngle;
			jd.enableMotor = joint->enableMotor;
			jd.maxMotorTorque = joint->maxMotorTorque;
			jd.motorSpeed = joint->motorSpeed;

			bJoint = world->CreateJoint(&jd);
		}
		break;
	case JointData::e_prismaticJoint:
		{
			b2PrismaticJointDef jd;

			PrismaticJoint* joint = static_cast<PrismaticJoint*>(const_cast<JointData*>(&data));

			std::map<BodyData*, b2Body*>::const_iterator 
				itrA = bodyMap.find(joint->bodyA),
				itrB = bodyMap.find(joint->bodyB);
			assert(itrA != bodyMap.end() && itrB != bodyMap.end());
			b2Body* bodyA = itrA->second;
			b2Body* bodyB = itrB->second;

			b2Vec2 axis(joint->localAxisA.x, joint->localAxisA.y);
			axis.Normalize();
			jd.Initialize(bodyA, bodyB, b2Vec2(0, 0), axis);
			jd.collideConnected = joint->collideConnected;
			jd.localAnchorA.Set(joint->localAnchorA.x / BOX2D_SCALE_FACTOR, joint->localAnchorA.y / BOX2D_SCALE_FACTOR);
			jd.localAnchorB.Set(joint->localAnchorB.x / BOX2D_SCALE_FACTOR, joint->localAnchorB.y / BOX2D_SCALE_FACTOR);
			jd.referenceAngle = joint->referenceAngle;
			jd.enableLimit = joint->enableLimit;
			jd.lowerTranslation = joint->lowerTranslation;
			jd.upperTranslation = joint->upperTranslation;
			jd.enableMotor = joint->enableMotor;
			jd.maxMotorForce = joint->maxMotorForce;
			jd.motorSpeed = joint->motorSpeed;

			bJoint = world->CreateJoint(&jd);
		}
		break;
	case JointData::e_distanceJoint:
		{
			b2DistanceJointDef jd;

			DistanceJoint* joint = static_cast<DistanceJoint*>(const_cast<JointData*>(&data));

			std::map<BodyData*, b2Body*>::const_iterator 
				itrA = bodyMap.find(joint->bodyA),
				itrB = bodyMap.find(joint->bodyB);
			assert(itrA != bodyMap.end() && itrB != bodyMap.end());
			jd.bodyA = itrA->second;
			jd.bodyB = itrB->second;
			jd.collideConnected = joint->collideConnected;
			jd.localAnchorA.Set(joint->localAnchorA.x / BOX2D_SCALE_FACTOR, joint->localAnchorA.y / BOX2D_SCALE_FACTOR);
			jd.localAnchorB.Set(joint->localAnchorB.x / BOX2D_SCALE_FACTOR, joint->localAnchorB.y / BOX2D_SCALE_FACTOR);
			jd.length = f2Math::getDistance(joint->getWorldAnchorA(), joint->getWorldAnchorB()) / BOX2D_SCALE_FACTOR;
			jd.frequencyHz = joint->frequencyHz;
			jd.dampingRatio = joint->dampingRatio;

			bJoint = world->CreateJoint(&jd);
		}
		break;
	case JointData::e_wheelJoint:
		{
			b2WheelJointDef jd;

			WheelJoint* joint = static_cast<WheelJoint*>(const_cast<JointData*>(&data));

			std::map<BodyData*, b2Body*>::const_iterator 
				itrA = bodyMap.find(joint->bodyA),
				itrB = bodyMap.find(joint->bodyB);
			assert(itrA != bodyMap.end() && itrB != bodyMap.end());
			b2Body* bodyA = itrA->second;
			b2Body* bodyB = itrB->second;

			f2Vec2 pos = joint->getWorldAnchorB() / BOX2D_SCALE_FACTOR;
			b2Vec2 axis(joint->localAxisA.x, joint->localAxisA.y);
			axis.Normalize();
			jd.Initialize(bodyA, bodyB, b2Vec2(pos.x, pos.y), axis);
			jd.enableMotor = joint->enableMotor;
			jd.maxMotorTorque = joint->maxMotorTorque;
			jd.motorSpeed = joint->motorSpeed;
			jd.frequencyHz = joint->frequencyHz;
			jd.dampingRatio = joint->dampingRatio;

			bJoint = world->CreateJoint(&jd);
		}
		break;
	default:
		assert(0);
	}

	return bJoint;
}