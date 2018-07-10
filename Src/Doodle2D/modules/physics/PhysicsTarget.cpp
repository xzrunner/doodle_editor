//#include "PhysicsTarget.h"
//
//#include "common/math.h"
//
//using namespace d2d;
//
//PhysicsTarget::PhysicsTarget(b2World* pWorld, b2Body* pBodyObj, 
//							 Vector& pTarget, float pFactor)
//	: m_target(pTarget)
//{
//	m_factor = pFactor;
//
//	b2BodyDef lEmptyBodyDef;
//	b2Body* lEmptyBody = pWorld->CreateBody(&lEmptyBodyDef);
//
//	b2MouseJointDef lMouseJointDef;
//	lMouseJointDef.bodyA = lEmptyBody;
//	lMouseJointDef.bodyB = pBodyObj;
//	lMouseJointDef.target = b2Vec2(0.0f, 0.0f);
//	lMouseJointDef.maxForce = 50.0f * pBodyObj->GetMass();
//	lMouseJointDef.dampingRatio = 1.0f;
//	lMouseJointDef.frequencyHz = 3.5f;
//	m_mouseJoint = (b2MouseJoint*) pWorld->CreateJoint(&lMouseJointDef);
//}
//
//void PhysicsTarget::setTarget(float pX, float pY)
//{
//	b2Vec2 lTarget(
//		(m_target.x + pX * m_factor) * BOX2D_SCALE_FACTOR_INVERSE,
//		(m_target.y + pY * m_factor) * BOX2D_SCALE_FACTOR_INVERSE
//		);
//	m_mouseJoint->SetTarget(lTarget);
//}