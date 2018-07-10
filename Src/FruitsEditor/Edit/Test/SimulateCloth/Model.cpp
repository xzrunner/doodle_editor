#include "Model.h"
#include "Blackboard.h"
#include "Dataset/Sprite.h"
#include "Dataset/Layer.h"
#include "Dataset/LayersMgr.h"
#include <Box2D/Box2D.h>

using namespace FEDITOR;
using namespace FEDITOR::SIMULATE_CLOTH;

Model::Model(const AbstractBlackboard* blackboard, b2World* world)
	: m_regularGrids(*this)
{
	m_blackboard = static_cast<Blackboard*>(const_cast<AbstractBlackboard*>(blackboard));
	m_world = world;

	Layer* bgLayer = new Layer(Layer::e_lowermost);
	m_bgSprite = new Sprite;
	bgLayer->addSprite(m_bgSprite);
	m_layers->addLayer(bgLayer);

	Layer* deformationLayer = new Layer(Layer::e_middle);
	deformationLayer->m_style.m_triangleStyle.color.set(0, 0, 0.5f, 0.5f);
	m_deformationSprite = new Sprite;
	deformationLayer->addSprite(m_deformationSprite);
	m_layers->addLayer(deformationLayer);

	m_ground = NULL;
}

Model::~Model()
{
	clearGridsPhyData();
	if (m_ground) m_world->DestroyBody(m_ground);
}

void Model::handleEvent(const Event& event)
{
	switch (event.getID())
	{
	case Blackboard::e_Step:
		stepUpdate();
		break;

	case Blackboard::e_openRegularTexture:
		m_regularGrids.loadFromFile(event.getInfo());
		break;
	case Blackboard::e_resetWeb:
		m_regularGrids.build();
		break;

	case Blackboard::e_resetJointsFrequency:
		resetJointsFrequency();
		break;
	case Blackboard::e_resetJointsDamping:
		resetJointsDamping();
		break;
	case Blackboard::e_resetNodesEdge:
		resetNodesEdge();
		break;
	}
}

void Model::stepUpdate()
{
	m_regularGrids.update();
}

void Model::clearGridsPhyData()
{
	for (size_t i = 0, n = m_joints.size(); i < n; ++i) 
		m_world->DestroyJoint(m_joints[i]);
	m_joints.clear();
	for (size_t i = 0, n = m_bodies.size(); i < n; ++i) 
		m_world->DestroyBody(m_bodies[i]);
	m_bodies.clear();
}

void Model::resetJointsFrequency()
{
	for (size_t i = 0, n = m_joints.size(); i < n; ++i)
	{
		b2DistanceJoint* joint = dynamic_cast<b2DistanceJoint*>(m_joints[i]);
		joint->SetFrequency(m_blackboard->m_frequencyHz);
	}
}

void Model::resetJointsDamping()
{
	for (size_t i = 0, n = m_joints.size(); i < n; ++i)
	{
		b2DistanceJoint* joint = dynamic_cast<b2DistanceJoint*>(m_joints[i]);
		joint->SetDampingRatio(m_blackboard->m_dampingRatio);
	}
}

void Model::resetNodesEdge()
{
	for (size_t i = 0, n = m_bodies.size(); i < n; ++i)
	{
		b2Body* body = m_bodies[i];

		body->DestroyFixture(body->GetFixtureList());

		b2PolygonShape shape;
		shape.SetAsBox(m_blackboard->m_nodeHalfEdge, m_blackboard->m_nodeHalfEdge);
		body->CreateFixture(&shape, 0.0f);
	}
}