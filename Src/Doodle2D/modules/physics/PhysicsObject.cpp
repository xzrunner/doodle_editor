//#include "PhysicsObject.h"
//
//#include "common/Log.h"
//#include "common/math.h"
//
//using namespace d2d;
//
//PhysicsObject::PhysicsObject(uint16 pCategory, uint16 pMask,int32_t pDiameter, 
//							 float pRestitution, b2World* pWorld)
//{
//	m_collide = false;
//
//	m_world = pWorld;
//	m_bodyObj = NULL;
//
//	b2BodyDef bodyDef;
//	bodyDef.type = b2_dynamicBody;
//	bodyDef.userData = this;
//	bodyDef.awake = true;
//	bodyDef.fixedRotation = true;
//
//	b2CircleShape shapeDef;
//	shapeDef.m_p = b2Vec2_zero;
//	shapeDef.m_radius = pDiameter * 0.5f * BOX2D_SCALE_FACTOR_INVERSE;
//
//	b2FixtureDef fixtureDef;
//	fixtureDef.shape = &shapeDef;
//	fixtureDef.density = 1.0f;
//	fixtureDef.friction = 0.0f;
//	fixtureDef.restitution = pRestitution;
//	fixtureDef.filter.categoryBits = pCategory;
//	fixtureDef.filter.maskBits = pMask;
//	fixtureDef.userData = this;
//
//	m_bodyObj = m_world->CreateBody(&bodyDef);
//	m_bodyObj->CreateFixture(&fixtureDef);
//	m_bodyObj->SetUserData(this);
//}
//
//PhysicsObject::PhysicsObject(uint16 pCategory, uint16 pMask, const std::vector<std::vector<Vector> >& vertices, 
//							 float pRestitution, b2World* pWorld)
//{
//	m_collide = false;
//
//	m_world = pWorld;
//	m_bodyObj = NULL;
//
//	b2BodyDef bodyDef;
//	bodyDef.type = b2_dynamicBody;
//	bodyDef.userData = this;
//	bodyDef.awake = true;
//	bodyDef.fixedRotation = true;
//
//	m_bodyObj = m_world->CreateBody(&bodyDef);
//	m_bodyObj->SetUserData(this);
//
//	for (size_t i = 0, n = vertices.size(); i < n; ++i)
//	{
//		b2PolygonShape shapeDef;
//		std::vector<b2Vec2> loop(vertices[i].size());
//		for (size_t j = 0, m = vertices[i].size(); j < m; ++j)
//		{
//			loop[j].x = vertices[i][j].x * BOX2D_SCALE_FACTOR_INVERSE;
//			loop[j].y = vertices[i][j].y * BOX2D_SCALE_FACTOR_INVERSE;
//		}
//		shapeDef.Set(&loop[0], vertices[i].size());
//
//
//		b2FixtureDef fixtureDef;
//		fixtureDef.shape = &shapeDef;
//		fixtureDef.density = 1.0f;
//		fixtureDef.friction = 0.0f;
//		fixtureDef.restitution = pRestitution;
//		fixtureDef.filter.categoryBits = pCategory;
//		fixtureDef.filter.maskBits = pMask;
//		fixtureDef.userData = this;
//
//		m_bodyObj->CreateFixture(&fixtureDef);
//	}
//}
//
//PhysicsTarget::ptr PhysicsObject::createTarget(float pFactor)
//{
//	return PhysicsTarget::ptr(new PhysicsTarget(m_world, m_bodyObj, m_location, pFactor));
//}
//
//void PhysicsObject::initialize(float pX, float pY, float pVelocityX, float pVelocityY)
//{
//	m_location.set(pX, pY);
//	b2Vec2 lPosition(pX * BOX2D_SCALE_FACTOR_INVERSE, pY * BOX2D_SCALE_FACTOR_INVERSE);
//	m_bodyObj->SetTransform(lPosition, 0.0f);
//	m_bodyObj->SetLinearVelocity(b2Vec2(pVelocityX, pVelocityY));
//}
//
//void PhysicsObject::update()
//{
//	m_location.set(
//		m_bodyObj->GetPosition().x * BOX2D_SCALE_FACTOR,
//		m_bodyObj->GetPosition().y * BOX2D_SCALE_FACTOR
//		);
//}