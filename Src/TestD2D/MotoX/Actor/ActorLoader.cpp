// #include "ActorLoader.h"
// #include "Actor.h"
// #include "Player.h"
// #include "Motorbike.h"
// 
// #include "Tools/connect_id_defs.h"
// 
// using namespace motox;
// 
// #ifdef D2D_WINDOWS
// ActorLoader::ActorLoader(Actor* actor)
// 	: m_actor(actor)
// 	, m_world(actor->m_physicsService->getWorld())
// 	, m_player(actor->m_player)
// 	, m_bike(actor->m_bike)
// {
// 	if (m_player && m_bike)
// 	{
// 		std::string path = RESOURCE_ROOT + ACTOR_DATA_FILEPATH;
// 		std::ifstream fin(path.c_str());
// 		if (fin.fail()) path = ACTOR_DATA_FILEPATH;
// 		fin.close();
// 
// 		load(path);
// 	}
// }
// #elif defined D2D_ANDROID_NATIVE
// ActorLoader::ActorLoader(Actor* actor, android_app* pApplication)
// 	: m_actor(actor)
// 	, m_world(actor->m_physicsService->getWorld())
// 	, m_player(actor->m_player)
// 	, m_bike(actor->m_bike)
// 	, m_pApplication(pApplication)
// {
// 	if (m_player && m_bike)
// 	{
// 		std::string path = ACTOR_DATA_FILEPATH;
// 		load(path);
// 	}
// }
// #elif defined D2D_ANDROID_JNI
// ActorLoader::ActorLoader(Actor* actor)
// 	: m_actor(actor)
// 	, m_world(actor->m_physicsService->getWorld())
// 	, m_player(actor->m_player)
// 	, m_bike(actor->m_bike)
// {
// 	if (m_player && m_bike)
// 	{
// 		std::string path = ACTOR_DATA_FILEPATH;
// 		load(path);
// 	}
// }
// #endif
// 
// void ActorLoader::load(const std::string& filepath)
// {
// #ifdef D2D_WINDOWS
// 	d2d::Resource resource(filepath);
// #elif defined D2D_ANDROID_NATIVE
// 	d2d::Resource resource(m_pApplication, filepath);
// #elif defined D2D_ANDROID_JNI
// 	d2d::Resource resource(filepath);
// #endif
// 	if (resource.open() != d2d::STATUS_OK)
// 		assert(0);
// 	const void *buffer = resource.bufferize();
// 	assert(buffer);
// 
// 	byte* ptr = static_cast<byte*>(const_cast<void*>(buffer));
// 	loadGraphicsAndBodies(&ptr);
// 	loadMotionParams(&ptr);
// 
// 	setCollisionFilter();
// 
// 	resource.close();
// }
// 
// void ActorLoader::loadGraphicsAndBodies(byte** ptr)
// {
// #ifdef D2D_WINDOWS
// 	std::string path = RESOURCE_ROOT + ACTOR_TEXTURE_FILEPATH;
// 
// 	std::ifstream fin(path.c_str());
// 	if (fin.fail()) path = ACTOR_TEXTURE_FILEPATH;
// 	fin.close();
// #elif defined D2D_ANDROID_NATIVE
// 	std::string path = ACTOR_TEXTURE_FILEPATH;
// #elif defined D2D_ANDROID_JNI
// 	std::string path = ACTOR_TEXTURE_FILEPATH;
// #endif
// 
// 	d2d::Texture* texture = m_actor->m_graphicsService->registerTexture(path);
// 	texture->load();
// 	m_actor->m_batch = new d2d::SpriteBatch(texture, 20, d2d::SpriteBatch::USAGE_STATIC);
// 
// 	int totWidth, totHeight;
// 	memcpy(&totWidth, *ptr, sizeof(int));
// 	*ptr += sizeof(int);
// 	memcpy(&totHeight, *ptr, sizeof(int));
// 	*ptr += sizeof(int);
// 
// 	size_t size = 0;
// 	memcpy(&size, *ptr, sizeof(size_t));
// 	*ptr += sizeof(size_t);
// 	for (size_t i = 0; i < size; ++i)
// 	{
// 		// Graphics
// 		int left, top, width, height;
// 		memcpy(&left, *ptr, sizeof(int));
// 		*ptr += sizeof(int);
// 		memcpy(&top, *ptr, sizeof(int));
// 		*ptr += sizeof(int);
// 		memcpy(&width, *ptr, sizeof(int));
// 		*ptr += sizeof(int);
// 		memcpy(&height, *ptr, sizeof(int));
// 		*ptr += sizeof(int);
// 
// 		switch (i)
// 		{
// 		case 0:
// 			m_player->m_parts[e_PartHead]->m_graphics = new d2d::GraphicsSprite(texture, left, top, 
// 				width, height, totWidth, totHeight);
// 			break;
// 		case 1:
// 			m_player->m_parts[e_PartBody]->m_graphics = new d2d::GraphicsSprite(texture, left, top, 
// 				width, height, totWidth, totHeight);
// 			break;
// 		case 2:
// 			m_player->m_parts[e_PartBigArmLeft]->m_graphics = new d2d::GraphicsSprite(texture, left, top, 
// 				width, height, totWidth, totHeight);
// 			m_player->m_parts[e_PartBigArmRight]->m_graphics = new d2d::GraphicsSprite(texture, left, top, 
// 				width, height, totWidth, totHeight);
// 			break;
// 		case 3:
// 			m_player->m_parts[e_PartSmallArmLeft]->m_graphics = new d2d::GraphicsSprite(texture, left, top, 
// 				width, height, totWidth, totHeight);
// 			m_player->m_parts[e_PartSmallArmRight]->m_graphics = new d2d::GraphicsSprite(texture, left, top, 
// 				width, height, totWidth, totHeight);
// 			break;
// 		case 4:
// 			m_player->m_parts[e_PartBigLegLeft]->m_graphics = new d2d::GraphicsSprite(texture, left, top, 
// 				width, height, totWidth, totHeight);
// 			m_player->m_parts[e_PartBigLegRight]->m_graphics = new d2d::GraphicsSprite(texture, left, top, 
// 				width, height, totWidth, totHeight);
// 			break;
// 		case 5:
// 			m_player->m_parts[e_PartSmallLegLeft]->m_graphics = new d2d::GraphicsSprite(texture, left, top, 
// 				width, height, totWidth, totHeight);
// 			m_player->m_parts[e_PartSmallLegRight]->m_graphics = new d2d::GraphicsSprite(texture, left, top, 
// 				width, height, totWidth, totHeight);
// 			break;
// 		case 6:
// 			m_bike->m_frontWheel->m_graphics = new d2d::GraphicsSprite(texture, left, top, 
// 				width, height, totWidth, totHeight);
// 			break;
// 		case 7:
// 			m_bike->m_backWheel->m_graphics = new d2d::GraphicsSprite(texture, left, top, 
// 				width, height, totWidth, totHeight);
// 			break;
// 		case 8:
// 			m_bike->m_body->m_graphics = new d2d::GraphicsSprite(texture, left, top, 
// 				width, height, totWidth, totHeight);
// 			break;
// 		}
// 
// 		// Physics
// 		int tag;
// 		memcpy(&tag, *ptr, sizeof(int));
// 		*ptr += sizeof(int);
// 		if (tag == 1)
// 		{
// 			int shapeTag;
// 			memcpy(&shapeTag, *ptr, sizeof(int));
// 			*ptr += sizeof(int);
// 			if (shapeTag < 0)
// 			{
// 				int diameter;
// 				memcpy(&diameter, *ptr, sizeof(int));
// 				*ptr += sizeof(int);
// 
// 				switch (i)
// 				{
// 				case 6:
// 					m_bike->m_frontWheel->m_physics = d2d::BodyFactory::createCircle(m_world, diameter * 0.5f);
// 					m_bike->m_frontWheel->m_physics->setFriction(g_wheelFriction);
// 					m_bike->m_frontWheel->m_physics->setDensity(g_motoDensity);
// 					break;
// 				case 7:
// 					m_bike->m_backWheel->m_physics = d2d::BodyFactory::createCircle(m_world, diameter * 0.5f);
// //					createTireTeeth(m_bike->m_backWheel->m_physics->getBody(), diameter * 0.5f);
// 					m_bike->m_backWheel->m_physics->setFriction(g_wheelFriction);
// 					m_bike->m_backWheel->m_physics->setDensity(g_motoDensity);
// 					break;
// 				}
// 			}
// 			else
// 			{
// 				std::vector<std::vector<d2d::Vector> > loops;
// 				loops.reserve(shapeTag);
// 				for (size_t j = 0; j < shapeTag; ++j)
// 				{
// 					std::vector<d2d::Vector> loop;
// 					size_t posSize;
// 					memcpy(&posSize, *ptr, sizeof(int));
// 					*ptr += sizeof(int);
// 					loop.reserve(posSize);
// 					for (size_t k = 0; k < posSize; ++k)
// 					{
// 						d2d::Vector pos;
// 						memcpy(&pos.x, *ptr, sizeof(float));
// 						*ptr += sizeof(float);
// 						memcpy(&pos.y, *ptr, sizeof(float));
// 						*ptr += sizeof(float);
// 						loop.push_back(pos);
// 					}
// 					loops.push_back(loop);
// 				}
// 
// 				switch (i)
// 				{
// 				case 0:
// 					m_player->m_parts[e_PartHead]->m_physics = d2d::BodyFactory::createPolygons(m_world, loops);
// 					m_player->m_parts[e_PartHead]->m_physics->setDensity(g_playerDensity);
// 					break;
// 				case 1:
// 					m_player->m_parts[e_PartBody]->m_physics = d2d::BodyFactory::createPolygons(m_world, loops);
// 					m_player->m_parts[e_PartBody]->m_physics->setDensity(g_playerDensity);
// 					break;
// 				case 2:
// 					m_player->m_parts[e_PartBigArmLeft]->m_physics = d2d::BodyFactory::createPolygons(m_world, loops);
// 					m_player->m_parts[e_PartBigArmRight]->m_physics = d2d::BodyFactory::createPolygons(m_world, loops);
// 					m_player->m_parts[e_PartBigArmLeft]->m_physics->setDensity(g_playerDensity);
// 					m_player->m_parts[e_PartBigArmRight]->m_physics->setDensity(g_playerDensity);
// 					break;
// 				case 3:
// 					m_player->m_parts[e_PartSmallArmLeft]->m_physics = d2d::BodyFactory::createPolygons(m_world, loops);
// 					m_player->m_parts[e_PartSmallArmRight]->m_physics = d2d::BodyFactory::createPolygons(m_world, loops);
// 					m_player->m_parts[e_PartSmallArmLeft]->m_physics->setDensity(g_playerDensity);
// 					m_player->m_parts[e_PartSmallArmRight]->m_physics->setDensity(g_playerDensity);
// 					break;
// 				case 4:
// 					m_player->m_parts[e_PartBigLegLeft]->m_physics = d2d::BodyFactory::createPolygons(m_world, loops);
// 					m_player->m_parts[e_PartBigLegRight]->m_physics = d2d::BodyFactory::createPolygons(m_world, loops);
// 					m_player->m_parts[e_PartBigLegLeft]->m_physics->setDensity(g_playerDensity);
// 					m_player->m_parts[e_PartBigLegRight]->m_physics->setDensity(g_playerDensity);
// 					break;
// 				case 5:
// 					m_player->m_parts[e_PartSmallLegLeft]->m_physics = d2d::BodyFactory::createPolygons(m_world, loops);
// 					m_player->m_parts[e_PartSmallLegRight]->m_physics = d2d::BodyFactory::createPolygons(m_world, loops);
// 					m_player->m_parts[e_PartSmallLegLeft]->m_physics->setDensity(g_playerDensity);
// 					m_player->m_parts[e_PartSmallLegRight]->m_physics->setDensity(g_playerDensity);
// 					break;
// 				case 8:
// 					m_bike->m_body->m_physics = d2d::BodyFactory::createPolygons(m_world, loops);
// 					m_bike->m_body->m_physics->setDensity(g_motoDensity);
// 					break;
// 				}
// 			}
// 		}
// 		else
// 		{
// //			assert(0);
// 		}
// 	}
// 
// 	for (size_t i = 0; i < PLAYER_PARTS_COUNT; ++i)
// 		m_player->m_parts[i]->m_physics->getBody()->SetUserData(new int(ACTOR_ID));
// 	m_bike->m_body->m_physics->getBody()->SetUserData(new int(ACTOR_ID));
// 	m_bike->m_frontWheel->m_physics->getBody()->SetUserData(new int(ACTOR_ID));
// 	m_bike->m_backWheel->m_physics->getBody()->SetUserData(new int(ACTOR_ID));
// }
// 
// void ActorLoader::loadMotionParams(byte** ptr)
// {
// 	// Location & Angle
// 	for (size_t i = 0; i < PARTS_COUNT; ++i)
// 	{
// 		d2d::Vector location;
// 		float angle;
// 		memcpy(&location.x, *ptr, sizeof(float));
// 		*ptr += sizeof(float);
// 		memcpy(&location.y, *ptr, sizeof(float));
// 		*ptr += sizeof(float);
// 		memcpy(&angle, *ptr, sizeof(float));
// 		*ptr += sizeof(float);
// 		if (i < PLAYER_PARTS_COUNT)
// 			m_player->m_parts[i]->setTransform(location, angle);
// 		else if (i == e_PartFrontWheel)
// 			m_bike->m_frontWheel->setTransform(location, angle);
// 		else if (i == e_PartBackWheel)
// 			m_bike->m_backWheel->setTransform(location, angle);
// 		else if (i == e_PartMotorBody)
// 			m_bike->m_body->setTransform(location, angle);
// 	}
// 
// 	// SpriteBatch
//  	m_actor->m_batch->add(*m_player->m_parts[e_PartBigLegLeft]->m_graphics);
//  	m_actor->m_batch->add(*m_player->m_parts[e_PartSmallLegLeft]->m_graphics);
//  	m_actor->m_batch->add(*m_player->m_parts[e_PartBigArmLeft]->m_graphics);
//  	m_actor->m_batch->add(*m_player->m_parts[e_PartSmallArmLeft]->m_graphics);
// 	m_actor->m_batch->add(*m_bike->m_frontWheel->m_graphics);
// 	m_actor->m_batch->add(*m_bike->m_backWheel->m_graphics);
// 	m_actor->m_batch->add(*m_bike->m_body->m_graphics);
// 	m_actor->m_batch->add(*m_player->m_parts[e_PartHead]->m_graphics);
//  	m_actor->m_batch->add(*m_player->m_parts[e_PartBigLegRight]->m_graphics);
//  	m_actor->m_batch->add(*m_player->m_parts[e_PartBody]->m_graphics);
//  	m_actor->m_batch->add(*m_player->m_parts[e_PartSmallLegRight]->m_graphics);
//  	m_actor->m_batch->add(*m_player->m_parts[e_PartBigArmRight]->m_graphics);
//  	m_actor->m_batch->add(*m_player->m_parts[e_PartSmallArmRight]->m_graphics);
// 
//  	// Joints
//  	createMorotbikeJoints();
//  	createPlayerJoints(ptr);
// }
// 
// void ActorLoader::setCollisionFilter()
// {
// 	b2Filter motoFilter, playerCollFilter, playerNoCollFilter;
// 
// 	motoFilter.categoryBits = MOTO_CATEGORY;
// 	motoFilter.maskBits = MOTO_MASK;
// 	motoFilter.groupIndex = MOTO_GROUP;
// 
// 	playerCollFilter.maskBits = DEFAULT_MASK;
// 	playerNoCollFilter.categoryBits = PLAYER_CATEGORY;
// 	playerNoCollFilter.maskBits = PLAYER_MASK;
// 	playerCollFilter.groupIndex = playerNoCollFilter.groupIndex = PLAYER_GROUP;
// 
// 	m_bike->m_frontWheel->m_physics->setCollisionFilter(motoFilter);
// 	m_bike->m_backWheel->m_physics->setCollisionFilter(motoFilter);
// 	m_bike->m_body->m_physics->setCollisionFilter(motoFilter);
// 
// 	for (size_t i = 0; i < PLAYER_PARTS_COUNT; ++i)
// 	{
// 		d2d::PhysicsBody* body = m_player->m_parts[i]->m_physics;
// 		if (i == e_PartHead || i == e_PartBody)
// 			body->setCollisionFilter(playerCollFilter);
// 		else
// 			body->setCollisionFilter(playerNoCollFilter);
// 	}
// }
// 
// void ActorLoader::createMorotbikeJoints()
// {
// 	b2WheelJointDef jd;
// 	b2Vec2 axis(0.0f, 1.0f);
// 
// 	b2Body *body = m_bike->m_body->m_physics->getBody(),
// 		*back = m_bike->m_backWheel->m_physics->getBody(),
// 		*front = m_bike->m_frontWheel->m_physics->getBody();
// 
// 	jd.Initialize(body, back, back->GetPosition(), axis);
// 	jd.collideConnected = false;
// 	jd.motorSpeed = 0.0f;
// 	jd.maxMotorTorque = g_motoTorque;
// 	jd.enableMotor = true;
// 	jd.frequencyHz = 5;
// 	jd.dampingRatio = 2;
// 	m_bike->m_jointBack = (b2WheelJoint*) m_world->CreateJoint(&jd);
// 
// 	jd.Initialize(body, front, front->GetPosition(), axis);
// 	jd.collideConnected = false;
// 	jd.motorSpeed = 0.0f;
// 	jd.maxMotorTorque = g_motoTorque;
// 	jd.enableMotor = true;
// 	jd.frequencyHz = 8;
// 	jd.dampingRatio = 3;
// 	m_bike->m_jointFront = (b2WheelJoint*) m_world->CreateJoint(&jd);
// }
// 
// void ActorLoader::createPlayerJoints(byte** ptr)
// {
// 	for (size_t i = 0; i < JOINTS_TYPE_COUNT; ++i)
// 	{
// 		JointDef def;
// 		d2d::Vector anchor;
// 
// 		memcpy(&def.positive_speed, *ptr, sizeof(float));
// 		*ptr += sizeof(float);
// 		memcpy(&def.negative_speed, *ptr, sizeof(float));
// 		*ptr += sizeof(float);
// 
// 		memcpy(&def.left_angle_small, *ptr, sizeof(float));
// 		*ptr += sizeof(float);
// 		memcpy(&def.left_angle_large, *ptr, sizeof(float));
// 		*ptr += sizeof(float);
// 		memcpy(&def.right_angle_small, *ptr, sizeof(float));
// 		*ptr += sizeof(float);
// 		memcpy(&def.right_angle_large, *ptr, sizeof(float));
// 		*ptr += sizeof(float);
// 
// 		memcpy(&def.max_torque, *ptr, sizeof(float));
// 		*ptr += sizeof(float);
// 
// 		memcpy(&anchor.x, *ptr, sizeof(float));
// 		*ptr += sizeof(float);
// 		memcpy(&anchor.y, *ptr, sizeof(float));
// 		*ptr += sizeof(float);
// 
// 		switch (i)
// 		{
// 		case e_JointTypeNeck:
// 			m_player->m_joints[e_JointNeck] = new Joint(m_world, def, anchor, m_player->m_parts[e_PartBody]->m_physics->getBody(), m_player->m_parts[e_PartHead]->m_physics->getBody(), true);
// 			break;
// 		case e_JointTypeShoulder:
// 			m_player->m_joints[e_JointShoulderL] = new Joint(m_world, def, anchor, m_player->m_parts[e_PartBody]->m_physics->getBody(), m_player->m_parts[e_PartBigArmLeft]->m_physics->getBody(), true);
// 			m_player->m_joints[e_JointShoulderR] = new Joint(m_world, def, anchor, m_player->m_parts[e_PartBody]->m_physics->getBody(), m_player->m_parts[e_PartBigArmRight]->m_physics->getBody(), true);
// 			break;
// 		case e_JointTypeElbow:
// 			m_player->m_joints[e_JointElbowL] = new Joint(m_world, def, anchor, m_player->m_parts[e_PartBigArmLeft]->m_physics->getBody(), m_player->m_parts[e_PartSmallArmLeft]->m_physics->getBody(), true);
// 			m_player->m_joints[e_JointElbowR] = new Joint(m_world, def, anchor, m_player->m_parts[e_PartBigArmRight]->m_physics->getBody(), m_player->m_parts[e_PartSmallArmRight]->m_physics->getBody(), true);
// 			break;
// 		case e_JointTypeHip:
// 			m_player->m_joints[e_JointHipL] = new Joint(m_world, def, anchor, m_player->m_parts[e_PartBody]->m_physics->getBody(), m_player->m_parts[e_PartBigLegLeft]->m_physics->getBody(), true);
// 			m_player->m_joints[e_JointHipR] = new Joint(m_world, def, anchor, m_player->m_parts[e_PartBody]->m_physics->getBody(), m_player->m_parts[e_PartBigLegRight]->m_physics->getBody(), true);
// 			break;
// 		case e_JointTypeKnee:
// 			m_player->m_joints[e_JointKneeL] = new Joint(m_world, def, anchor, m_player->m_parts[e_PartBigLegLeft]->m_physics->getBody(), m_player->m_parts[e_PartSmallLegLeft]->m_physics->getBody(), true);
// 			m_player->m_joints[e_JointKneeR] = new Joint(m_world, def, anchor, m_player->m_parts[e_PartBigLegRight]->m_physics->getBody(), m_player->m_parts[e_PartSmallLegRight]->m_physics->getBody(), true);
// 			break;
// 		case e_JointTypeHand:
// 			m_player->m_joints[e_JointHandL] = new Joint(m_world, def, anchor, m_player->m_parts[e_PartSmallArmLeft]->m_physics->getBody(), m_bike->m_body->m_physics->getBody(), false);
// 			m_player->m_joints[e_JointHandR] = new Joint(m_world, def, anchor, m_player->m_parts[e_PartSmallArmRight]->m_physics->getBody(), m_bike->m_body->m_physics->getBody(), false);
// 			break;
// 		case e_JointTypeFoot:
// 			m_player->m_joints[e_JointFootL] = new Joint(m_world, def, anchor, m_player->m_parts[e_PartSmallLegLeft]->m_physics->getBody(), m_bike->m_body->m_physics->getBody(), false);
// 			m_player->m_joints[e_JointFootR] = new Joint(m_world, def, anchor, m_player->m_parts[e_PartSmallLegRight]->m_physics->getBody(), m_bike->m_body->m_physics->getBody(), false);
// 			break;
// 		}
// 	}
// }
// 
// void ActorLoader::createTireTeeth(b2Body* body, float radius)
// {
// 	const float edge = radius * 0.14f;
// 	const float ratio = 0.5f;
// 
// 	for (size_t i = 0; i < 12; ++i)
// 	{
// 		//const float angle = 2 * PI * i / 12;
// 		//tri[0].x = radius * (2 * PI * i / 12)
// 
// 		const float angle = 2 * d2d::PI * i / 12;
// 		const float sinVal = sin(angle),
// 			cosVal = cos(angle);
// 		d2d::Vector p0;
// 		p0.x = (radius - edge * ratio) * cosVal;
// 		p0.y = (radius - edge * ratio) * sinVal;
// 		d2d::Vector c;
// 		c.x = (radius - edge * ratio + edge) * cosVal;
// 		c.y = (radius - edge * ratio + edge) * sinVal;
// 		d2d::Vector offset = (p0 - c) / 1.9f;
// 
// 		b2Vec2 tri[4];
// 		tri[0].x = p0.x * d2d::BOX2D_SCALE_FACTOR_INVERSE;
// 		tri[0].y = p0.y * d2d::BOX2D_SCALE_FACTOR_INVERSE;
// 
// 		tri[0].x = (-offset.y + p0.x) * d2d::BOX2D_SCALE_FACTOR_INVERSE;
// 		tri[0].y = (offset.x + p0.y) * d2d::BOX2D_SCALE_FACTOR_INVERSE;
// 		tri[1].x = (-offset.y + c.x) * d2d::BOX2D_SCALE_FACTOR_INVERSE;
// 		tri[1].y = (offset.x + c.y) * d2d::BOX2D_SCALE_FACTOR_INVERSE;
// 		tri[2].x = (offset.y + c.x) * d2d::BOX2D_SCALE_FACTOR_INVERSE;
// 		tri[2].y = (-offset.x + c.y) * d2d::BOX2D_SCALE_FACTOR_INVERSE;
// 		tri[3].x = (offset.y + p0.x) * d2d::BOX2D_SCALE_FACTOR_INVERSE;
// 		tri[3].y = (-offset.x + p0.y) * d2d::BOX2D_SCALE_FACTOR_INVERSE;
// 
// 		b2PolygonShape shape;
// 		shape.Set(&tri[0], 4);
// 
// 		b2FixtureDef fd;
// 		fd.shape = &shape;
// 		fd.density = 0.2f;
// 		fd.friction = 1.0f;
// 
// 		body->CreateFixture(&fd);
// 	}
// }