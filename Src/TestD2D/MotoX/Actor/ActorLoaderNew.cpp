#include "ActorLoaderNew.h"
#include "Actor.h"
#include "Player.h"
#include "Motorbike.h"

#include "Tools/connect_id_defs.h"

using namespace motox;

#ifdef D2D_WINDOWS
ActorLoaderNew::ActorLoaderNew(Actor* actor)
	: m_actor(actor)
	, m_world(actor->m_physicsService->getWorld())
	, m_player(actor->m_player)
	, m_bike(actor->m_bike)
{
	if (m_player && m_bike)
	{
		std::string path = RESOURCE_ROOT + ACTOR_DATA_FILENAME;
		std::ifstream fin(path.c_str());
		if (fin.fail()) path = ACTOR_DATA_FILENAME;
		fin.close();

		load(path);
	}
}
#elif defined D2D_ANDROID_NATIVE
ActorLoaderNew::ActorLoaderNew(Actor* actor, android_app* pApplication)
	: m_actor(actor)
	, m_world(actor->m_physicsService->getWorld())
	, m_player(actor->m_player)
	, m_bike(actor->m_bike)
	, m_pApplication(pApplication)
{
	if (m_player && m_bike)
	{
		std::string path = ACTOR_DATA_FILENAME;
		load(path);
	}
}
#elif defined D2D_ANDROID_JNI
ActorLoaderNew::ActorLoaderNew(Actor* actor)
	: m_actor(actor)
	, m_world(actor->m_physicsService->getWorld())
	, m_player(actor->m_player)
	, m_bike(actor->m_bike)
{
	if (m_player && m_bike)
	{
		std::string path = ACTOR_DATA_FILENAME;
		load(path);
	}
}
#endif

void ActorLoaderNew::load(const std::string& filepath)
{
#ifdef D2D_WINDOWS
	d2d::Resource resource(filepath);
#elif defined D2D_ANDROID_NATIVE
	d2d::Resource resource(m_pApplication, filepath);
#elif defined D2D_ANDROID_JNI
	d2d::Resource resource(filepath);
#endif
	if (resource.open() != d2d::STATUS_OK)
		assert(0);
	const void *buffer = resource.bufferize();
	assert(buffer);

	byte* ptr = static_cast<byte*>(const_cast<void*>(buffer));
	loadMergedAndBounding(ptr);
	loadPlayerInfo(ptr);
	loadMotorbikeInfo(ptr);

	setCollisionFilter();

	resource.close();
}

void ActorLoaderNew::loadMergedAndBounding(byte*& ptr)
{
#ifdef D2D_WINDOWS
	std::string path = RESOURCE_ROOT + ACTOR_TEXTURE_FILENAME;

	std::ifstream fin(path.c_str());
	if (fin.fail()) path = ACTOR_TEXTURE_FILENAME;
	fin.close();
#elif defined D2D_ANDROID_NATIVE
	std::string path = ACTOR_TEXTURE_FILENAME;
#elif defined D2D_ANDROID_JNI
	std::string path = ACTOR_TEXTURE_FILENAME;
#endif

	d2d::Texture* texture = m_actor->m_graphicsService->registerTexture(path);
	texture->load();
	m_actor->m_batch = new d2d::SpriteBatch(texture, 20, d2d::SpriteBatch::USAGE_STATIC);

	int totWidth, totHeight;
	memcpy(&totWidth, ptr, sizeof(int));
	ptr += sizeof(int);
	memcpy(&totHeight, ptr, sizeof(int));
	ptr += sizeof(int);

	size_t size = 0;
	memcpy(&size, ptr, sizeof(size_t));
	ptr += sizeof(size_t);
	for (size_t i = 0; i < size; ++i)
	{
		// Graphics
		int left, top, width, height;
		memcpy(&left, ptr, sizeof(int));
		ptr += sizeof(int);
		memcpy(&top, ptr, sizeof(int));
		ptr += sizeof(int);
		memcpy(&width, ptr, sizeof(int));
		ptr += sizeof(int);
		memcpy(&height, ptr, sizeof(int));
		ptr += sizeof(int);

		switch (i)
		{
		case 0:
			m_player->m_parts[e_PartHead]->m_graphics = new d2d::GraphicsSprite(texture, left, top, 
				width, height, totWidth, totHeight);
			break;
		case 1:
			m_player->m_parts[e_PartBody]->m_graphics = new d2d::GraphicsSprite(texture, left, top, 
				width, height, totWidth, totHeight);
			break;
		case 2:
			m_player->m_parts[e_PartBigArmLeft]->m_graphics = new d2d::GraphicsSprite(texture, left, top, 
				width, height, totWidth, totHeight);
			m_player->m_parts[e_PartBigArmRight]->m_graphics = new d2d::GraphicsSprite(texture, left, top, 
				width, height, totWidth, totHeight);
			break;
		case 3:
			m_player->m_parts[e_PartSmallArmLeft]->m_graphics = new d2d::GraphicsSprite(texture, left, top, 
				width, height, totWidth, totHeight);
			m_player->m_parts[e_PartSmallArmRight]->m_graphics = new d2d::GraphicsSprite(texture, left, top, 
				width, height, totWidth, totHeight);
			break;
		case 4:
			m_player->m_parts[e_PartBigLegLeft]->m_graphics = new d2d::GraphicsSprite(texture, left, top, 
				width, height, totWidth, totHeight);
			m_player->m_parts[e_PartBigLegRight]->m_graphics = new d2d::GraphicsSprite(texture, left, top, 
				width, height, totWidth, totHeight);
			break;
		case 5:
			m_player->m_parts[e_PartSmallLegLeft]->m_graphics = new d2d::GraphicsSprite(texture, left, top, 
				width, height, totWidth, totHeight);
			m_player->m_parts[e_PartSmallLegRight]->m_graphics = new d2d::GraphicsSprite(texture, left, top, 
				width, height, totWidth, totHeight);
			break;
		case 6:
			m_bike->m_backWheel->m_graphics = new d2d::GraphicsSprite(texture, left, top, 
				width, height, totWidth, totHeight);
			break;
		case 7:
			m_bike->m_frontWheel->m_graphics = new d2d::GraphicsSprite(texture, left, top, 
				width, height, totWidth, totHeight);
			break;
		case 8:
			m_bike->m_body->m_graphics = new d2d::GraphicsSprite(texture, left, top, 
				width, height, totWidth, totHeight);
			break;
		case 9:
			m_bike->m_backDamping->m_graphics = new d2d::GraphicsSprite(texture, left, top, 
				width, height, totWidth, totHeight);
			break;
		case 10:
			m_bike->m_frontDamping->m_graphics = new d2d::GraphicsSprite(texture, left, top, 
				width, height, totWidth, totHeight);
			break;
		}

		// Physics
		int tag;
		memcpy(&tag, ptr, sizeof(int));
		ptr += sizeof(int);
		if (tag == 1)
		{
			int shapeTag;
			memcpy(&shapeTag, ptr, sizeof(int));
			ptr += sizeof(int);

			assert(shapeTag >= 0);

			std::vector<std::vector<d2d::Vector> > loops;
			loops.reserve(shapeTag);
			for (size_t j = 0; j < shapeTag; ++j)
			{
				std::vector<d2d::Vector> loop;
				size_t posSize;
				memcpy(&posSize, ptr, sizeof(int));
				ptr += sizeof(int);
				loop.reserve(posSize);
				for (size_t k = 0; k < posSize; ++k)
				{
					d2d::Vector pos;
					memcpy(&pos.x, ptr, sizeof(float));
					ptr += sizeof(float);
					memcpy(&pos.y, ptr, sizeof(float));
					ptr += sizeof(float);
					loop.push_back(pos);
				}
				loops.push_back(loop);
			}

			switch (i)
			{
			case 0:
				m_player->m_parts[e_PartHead]->m_physics = d2d::BodyFactory::createPolygons(m_world, loops);
				m_player->m_parts[e_PartHead]->m_physics->setDensity(g_playerDensity);
				break;
			case 1:
				m_player->m_parts[e_PartBody]->m_physics = d2d::BodyFactory::createPolygons(m_world, loops);
				m_player->m_parts[e_PartBody]->m_physics->setDensity(g_playerDensity);
				break;
			case 2:
				m_player->m_parts[e_PartBigArmLeft]->m_physics = d2d::BodyFactory::createPolygons(m_world, loops);
				m_player->m_parts[e_PartBigArmRight]->m_physics = d2d::BodyFactory::createPolygons(m_world, loops);
				m_player->m_parts[e_PartBigArmLeft]->m_physics->setDensity(g_playerDensity);
				m_player->m_parts[e_PartBigArmRight]->m_physics->setDensity(g_playerDensity);
				break;
			case 3:
				m_player->m_parts[e_PartSmallArmLeft]->m_physics = d2d::BodyFactory::createPolygons(m_world, loops);
				m_player->m_parts[e_PartSmallArmRight]->m_physics = d2d::BodyFactory::createPolygons(m_world, loops);
				m_player->m_parts[e_PartSmallArmLeft]->m_physics->setDensity(g_playerDensity);
				m_player->m_parts[e_PartSmallArmRight]->m_physics->setDensity(g_playerDensity);
				break;
			case 4:
				m_player->m_parts[e_PartBigLegLeft]->m_physics = d2d::BodyFactory::createPolygons(m_world, loops);
				m_player->m_parts[e_PartBigLegRight]->m_physics = d2d::BodyFactory::createPolygons(m_world, loops);
				m_player->m_parts[e_PartBigLegLeft]->m_physics->setDensity(g_playerDensity);
				m_player->m_parts[e_PartBigLegRight]->m_physics->setDensity(g_playerDensity);
				break;
			case 5:
				m_player->m_parts[e_PartSmallLegLeft]->m_physics = d2d::BodyFactory::createPolygons(m_world, loops);
				m_player->m_parts[e_PartSmallLegRight]->m_physics = d2d::BodyFactory::createPolygons(m_world, loops);
				m_player->m_parts[e_PartSmallLegLeft]->m_physics->setDensity(g_playerDensity);
				m_player->m_parts[e_PartSmallLegRight]->m_physics->setDensity(g_playerDensity);
				break;
			}
		}
	}

	for (size_t i = 0; i < PLAYER_PARTS_COUNT; ++i)
		m_player->m_parts[i]->m_physics->getBody()->SetUserData(new int(ACTOR_ID));
}

void ActorLoaderNew::loadPlayerInfo(byte*& ptr)
{
	// Location & Angle
	for (size_t i = 0; i < PARTS_COUNT - 2 - 2; ++i)
	{
		memcpy(&m_locations[i].x, ptr, sizeof(float));
		ptr += sizeof(float);
		memcpy(&m_locations[i].y, ptr, sizeof(float));
		ptr += sizeof(float);
		memcpy(&m_angles[i], ptr, sizeof(float));
		ptr += sizeof(float);
		if (i < PLAYER_PARTS_COUNT)
			m_player->m_parts[i]->setTransform(m_locations[i], m_angles[i]);
	}

	// Player's joints
	for (size_t i = 0; i < JOINTS_TYPE_COUNT; ++i)
	{
		memcpy(&m_playerJointDefs[i].positive_speed, ptr, sizeof(float));
		ptr += sizeof(float);
		memcpy(&m_playerJointDefs[i].negative_speed, ptr, sizeof(float));
		ptr += sizeof(float);

		memcpy(&m_playerJointDefs[i].left_angle_small, ptr, sizeof(float));
		ptr += sizeof(float);
		memcpy(&m_playerJointDefs[i].left_angle_large, ptr, sizeof(float));
		ptr += sizeof(float);
		memcpy(&m_playerJointDefs[i].right_angle_small, ptr, sizeof(float));
		ptr += sizeof(float);
		memcpy(&m_playerJointDefs[i].right_angle_large, ptr, sizeof(float));
		ptr += sizeof(float);

		memcpy(&m_playerJointDefs[i].max_torque, ptr, sizeof(float));
		ptr += sizeof(float);

		memcpy(&m_anchors[i].x, ptr, sizeof(float));
		ptr += sizeof(float);
		memcpy(&m_anchors[i].y, ptr, sizeof(float));
		ptr += sizeof(float);
	}

	// SpriteBatch
	m_actor->m_batch->add(*m_player->m_parts[e_PartBigLegLeft]->m_graphics);
	m_actor->m_batch->add(*m_player->m_parts[e_PartSmallLegLeft]->m_graphics);
	m_actor->m_batch->add(*m_player->m_parts[e_PartBigArmLeft]->m_graphics);
	m_actor->m_batch->add(*m_player->m_parts[e_PartSmallArmLeft]->m_graphics);
	m_actor->m_batch->add(*m_bike->m_backWheel->m_graphics);
	m_actor->m_batch->add(*m_bike->m_frontWheel->m_graphics);
	m_actor->m_batch->add(*m_bike->m_body->m_graphics);
	m_actor->m_batch->add(*m_bike->m_backDamping->m_graphics);
	m_actor->m_batch->add(*m_bike->m_frontDamping->m_graphics);
	m_actor->m_batch->add(*m_player->m_parts[e_PartHead]->m_graphics);
	m_actor->m_batch->add(*m_player->m_parts[e_PartBigLegRight]->m_graphics);
	m_actor->m_batch->add(*m_player->m_parts[e_PartBody]->m_graphics);
	m_actor->m_batch->add(*m_player->m_parts[e_PartSmallLegRight]->m_graphics);
	m_actor->m_batch->add(*m_player->m_parts[e_PartBigArmRight]->m_graphics);
	m_actor->m_batch->add(*m_player->m_parts[e_PartSmallArmRight]->m_graphics);
}

void ActorLoaderNew::loadMotorbikeInfo(byte*& ptr)
{
	d2d::PhysicsParser parser;
	parser.parser(ptr);
	
	// motorbike's bodies

	m_bike->m_backWheel->m_physics = d2d::BodyFactory::createBody(m_world, *parser.bodies[0]);
	m_bike->m_frontWheel->m_physics = d2d::BodyFactory::createBody(m_world, *parser.bodies[1]);
	m_bike->m_body->m_physics = d2d::BodyFactory::createBody(m_world, *parser.bodies[2]);
// 	m_bike->m_backDamping->m_physics = d2d::BodyFactory::createBody(m_world, *parser.bodies[3]);
// 	m_bike->m_frontDamping->m_physics = d2d::BodyFactory::createBody(m_world, *parser.bodies[4]);

	m_bike->m_backWheel->m_physics->getBody()->SetUserData(new int(ACTOR_ID));
	m_bike->m_frontWheel->m_physics->getBody()->SetUserData(new int(ACTOR_ID));
	m_bike->m_body->m_physics->getBody()->SetUserData(new int(ACTOR_ID));
// 	m_bike->m_backDamping->m_physics->getBody()->SetUserData(new int(ACTOR_ID));
// 	m_bike->m_frontDamping->m_physics->getBody()->SetUserData(new int(ACTOR_ID));

	// motorbike's damping info

	m_bike->m_frontDelta = parser.bodies[4]->angle - parser.bodies[2]->angle;
	m_bike->m_frontOffset = parser.bodies[4]->location - parser.bodies[1]->location;

	m_bike->m_backDampingLocal = static_cast<d2d::PhysicsParser::RevoluteJoint*>(parser.joints[2])->localAnchorA;
	m_bike->m_backBodyLocal = static_cast<d2d::PhysicsParser::RevoluteJoint*>(parser.joints[3])->localAnchorB;

	// motorbike's joints

	std::vector<b2Body*> bodies;
	bodies.push_back(m_bike->m_backWheel->m_physics->getBody());
	bodies.push_back(m_bike->m_frontWheel->m_physics->getBody());
	bodies.push_back(m_bike->m_body->m_physics->getBody());
// 	bodies.push_back(m_bike->m_backDamping->m_physics->getBody());
// 	bodies.push_back(m_bike->m_frontDamping->m_physics->getBody());

  	m_bike->m_frontJoint = static_cast<b2WheelJoint*>(d2d::JointFactory::createJoint(m_world, *parser.joints[0], bodies));
 // 	m_bike->m_backJoint = static_cast<b2RevoluteJoint*>(d2d::JointFactory::createJoint(m_world, *parser.joints[1], bodies));
	m_bike->m_backJoint = static_cast<b2WheelJoint*>(d2d::JointFactory::createJoint(m_world, *parser.joints[1], bodies));
//  	m_bike->m_joint3 = d2d::JointFactory::createJoint(m_world, *parser.joints[2], bodies);
//  	m_bike->m_joint4 = d2d::JointFactory::createJoint(m_world, *parser.joints[3], bodies);

	// player's joints
	for (size_t i = 0; i < JOINTS_TYPE_COUNT; ++i)
	{
		switch (i)
		{
		case e_JointTypeNeck:
			m_player->m_joints[e_JointNeck] = new Joint(m_world, m_playerJointDefs[i], m_anchors[i], m_player->m_parts[e_PartBody]->m_physics->getBody(), m_player->m_parts[e_PartHead]->m_physics->getBody(), true);
			break;
		case e_JointTypeShoulder:
			m_player->m_joints[e_JointShoulderL] = new Joint(m_world, m_playerJointDefs[i], m_anchors[i], m_player->m_parts[e_PartBody]->m_physics->getBody(), m_player->m_parts[e_PartBigArmLeft]->m_physics->getBody(), true);
			m_player->m_joints[e_JointShoulderR] = new Joint(m_world, m_playerJointDefs[i], m_anchors[i], m_player->m_parts[e_PartBody]->m_physics->getBody(), m_player->m_parts[e_PartBigArmRight]->m_physics->getBody(), true);
			break;
		case e_JointTypeElbow:
			m_player->m_joints[e_JointElbowL] = new Joint(m_world, m_playerJointDefs[i], m_anchors[i], m_player->m_parts[e_PartBigArmLeft]->m_physics->getBody(), m_player->m_parts[e_PartSmallArmLeft]->m_physics->getBody(), true);
			m_player->m_joints[e_JointElbowR] = new Joint(m_world, m_playerJointDefs[i], m_anchors[i], m_player->m_parts[e_PartBigArmRight]->m_physics->getBody(), m_player->m_parts[e_PartSmallArmRight]->m_physics->getBody(), true);
			break;
		case e_JointTypeHip:
			m_player->m_joints[e_JointHipL] = new Joint(m_world, m_playerJointDefs[i], m_anchors[i], m_player->m_parts[e_PartBody]->m_physics->getBody(), m_player->m_parts[e_PartBigLegLeft]->m_physics->getBody(), true);
			m_player->m_joints[e_JointHipR] = new Joint(m_world, m_playerJointDefs[i], m_anchors[i], m_player->m_parts[e_PartBody]->m_physics->getBody(), m_player->m_parts[e_PartBigLegRight]->m_physics->getBody(), true);
			break;
		case e_JointTypeKnee:
			m_player->m_joints[e_JointKneeL] = new Joint(m_world, m_playerJointDefs[i], m_anchors[i], m_player->m_parts[e_PartBigLegLeft]->m_physics->getBody(), m_player->m_parts[e_PartSmallLegLeft]->m_physics->getBody(), true);
			m_player->m_joints[e_JointKneeR] = new Joint(m_world, m_playerJointDefs[i], m_anchors[i], m_player->m_parts[e_PartBigLegRight]->m_physics->getBody(), m_player->m_parts[e_PartSmallLegRight]->m_physics->getBody(), true);
			break;
		case e_JointTypeHand:
			m_player->m_joints[e_JointHandL] = new Joint(m_world, m_playerJointDefs[i], m_anchors[i], m_player->m_parts[e_PartSmallArmLeft]->m_physics->getBody(), m_bike->m_body->m_physics->getBody(), false);
			m_player->m_joints[e_JointHandR] = new Joint(m_world, m_playerJointDefs[i], m_anchors[i], m_player->m_parts[e_PartSmallArmRight]->m_physics->getBody(), m_bike->m_body->m_physics->getBody(), false);
			break;
		case e_JointTypeFoot:
			m_player->m_joints[e_JointFootL] = new Joint(m_world, m_playerJointDefs[i], m_anchors[i], m_player->m_parts[e_PartSmallLegLeft]->m_physics->getBody(), m_bike->m_body->m_physics->getBody(), false);
			m_player->m_joints[e_JointFootR] = new Joint(m_world, m_playerJointDefs[i], m_anchors[i], m_player->m_parts[e_PartSmallLegRight]->m_physics->getBody(), m_bike->m_body->m_physics->getBody(), false);
			break;
		}
	}
}

void ActorLoaderNew::setCollisionFilter()
{
	b2Filter motoFilter, playerCollFilter, playerNoCollFilter;

	motoFilter.categoryBits = MOTO_CATEGORY;
	motoFilter.maskBits = MOTO_MASK;
	motoFilter.groupIndex = MOTO_GROUP;

	playerCollFilter.maskBits = DEFAULT_MASK;
	playerNoCollFilter.categoryBits = PLAYER_CATEGORY;
	playerNoCollFilter.maskBits = PLAYER_MASK;
	playerCollFilter.groupIndex = playerNoCollFilter.groupIndex = PLAYER_GROUP;

	m_bike->m_frontWheel->m_physics->setCollisionFilter(motoFilter);
	m_bike->m_backWheel->m_physics->setCollisionFilter(motoFilter);
	m_bike->m_body->m_physics->setCollisionFilter(motoFilter);

	for (size_t i = 0; i < PLAYER_PARTS_COUNT; ++i)
	{
		d2d::PhysicsBody* body = m_player->m_parts[i]->m_physics;
		if (i == e_PartHead || i == e_PartBody)
			body->setCollisionFilter(playerCollFilter);
		else
			body->setCollisionFilter(playerNoCollFilter);
	}
}