#include "Model.h"
#include "Blackboard.h"
#include "../../../Dataset/CircleBody.h"
#include "../../../Dataset/Sprite.h"
#include "../../../Dataset/Layer.h"
#include "../../../Dataset/LayersMgr.h"
#include <Box2D/Box2D.h>

using namespace FEDITOR;
using namespace FEDITOR::BASKETBALL;

Model::Model(const AbstractBlackboard* blackboard, b2World* world)
{
	m_blackboard = static_cast<Blackboard*>(const_cast<AbstractBlackboard*>(blackboard));
	m_world = world;
	initLayers();
}

Model::~Model()
{
}

void Model::handleEvent(const Event& event)
{
}

void Model::initLayers()
{
	initGround();
	initBasketAndNet();
}

void Model::initGround()
{
	b2BodyDef bd;
	m_ground = m_world->CreateBody(&bd);

	b2Vec2 vertexs[] = {
		b2Vec2(-40, -24),
		b2Vec2(40, -24),
		b2Vec2(40, 24),
		b2Vec2(-40, 24)
	};

	b2ChainShape shape;
	shape.CreateLoop(vertexs, 4);

	m_ground->CreateFixture(&shape, 1.0f);
}

void Model::initBasketAndNet()
{
	Layer* layer = new Layer(Layer::e_middle);
	m_layers->addLayer(layer);

	//////////////////////////////////////////////////////////////////////////

	Sprite* ball = new Sprite;
	CircleBody* body = new CircleBody(m_world, 1.0f);
	ball->setBody(body);

	ball->setTransform(f2Vec2(10.0f, 10.0f), 0.0f);

	layer->addSprite(ball);

	//////////////////////////////////////////////////////////////////////////

	const float totWidth = 4.0f, totHeight = 5.0f;
	const int colCount = 10, rowCount = 10;
	const float halfNodeEdge = 0.05f;

	// bodies
	b2PolygonShape shape;
	shape.SetAsBox(halfNodeEdge, halfNodeEdge);
	b2BodyDef bd;
	bd.type = b2_dynamicBody;

	const float xOffset = - totWidth * 0.5f,
		yOffset = - totHeight * 0.5f;
	const float wGrid = totWidth / (colCount - 1),
		hGrid = totHeight / (rowCount - 1);
	for (size_t i = 0; i < rowCount; ++i)
	{
		for (size_t j = 0; j < colCount; ++j)
		{
			bd.position.Set(wGrid * j + xOffset, hGrid * i + yOffset);

			if (i == rowCount - 1) 
				bd.type = b2_staticBody;
			else 
				bd.type = b2_dynamicBody;

			b2Body* body = m_world->CreateBody(&bd);
			body->CreateFixture(&shape, 0.01f);
			m_bodies.push_back(body);
		}
	}

	// Joints
	b2DistanceJointDef jd;
	b2Vec2 p1, p2, d;
	jd.frequencyHz = 5.0f;
	jd.dampingRatio = 0.9f;
	// joints grids
	for (size_t i = 0; i < rowCount; ++i)
	{
		for (size_t j = 1; j < colCount; ++j)
		{
			jd.bodyA = m_bodies[i * colCount + j - 1];
			jd.bodyB = m_bodies[i * colCount + j];
//			if (!isConnectCenter)
			{
				jd.localAnchorA.Set(halfNodeEdge, 0.0f);
				jd.localAnchorB.Set(-halfNodeEdge, 0.0f);
			}
			p1 = jd.bodyA->GetWorldPoint(jd.localAnchorA);
			p2 = jd.bodyB->GetWorldPoint(jd.localAnchorB);
			d = p2 - p1;
			jd.length = d.Length();
			b2Joint* joint = m_world->CreateJoint(&jd);
			m_joints.push_back(joint);
		}
	}
	for (size_t i = 0; i < colCount; ++i)
	{
		for (size_t j = 1; j < rowCount; ++j)
		{
			jd.bodyA = m_bodies[(j - 1) * colCount + i];
			jd.bodyB = m_bodies[j * colCount + i];
//			if (!isConnectCenter)
			{
				jd.localAnchorA.Set(0.0f, halfNodeEdge);
				jd.localAnchorB.Set(0.0f, -halfNodeEdge);
			}
			p1 = jd.bodyA->GetWorldPoint(jd.localAnchorA);
			p2 = jd.bodyB->GetWorldPoint(jd.localAnchorB);
			d = p2 - p1;
			jd.length = d.Length();
			b2Joint* joint = m_world->CreateJoint(&jd);
			m_joints.push_back(joint);
		}
	}
}