#include "TrackChains.h"

#include "Tools/defs.h"

using namespace motox;

TrackChains::TrackChains(d2d::Context* pContext,
						 int scene, int level)
{
	std::string path_fix = d2d::int2String(scene) + "/" + d2d::int2String(level) + "/";

	m_physicsService = pContext->m_physicsService;

#ifdef D2D_WINDOWS
	std::string path = RESOURCE_ROOT + path_fix + TRACK_CHAINS_FILENAME;

	std::ifstream fin(path.c_str());
	if (fin.fail()) path = path_fix + TRACK_CHAINS_FILENAME;
	fin.close();
#elif defined D2D_ANDROID_NATIVE
	m_pApplication = pContext->m_pApplication;
	std::string path = path_fix + TRACK_CHAINS_FILENAME;
#elif defined D2D_ANDROID_JNI
	std::string path = path_fix + TRACK_CHAINS_FILENAME;
#endif
	loadFromFile(path);
}

TrackChains::~TrackChains()
{
	b2World* world = m_physicsService->getWorld();
	for (size_t i = 0, n = m_bodies.size(); i < n; ++i)
		world->DestroyBody(m_bodies[i]);
}

void TrackChains::draw() const
{
  	glLineWidth(2.0f);
  	for (size_t i = 0, n = m_chains.size(); i < n; ++i)
  		d2d::DrawingPrimitives::drawPolyline(m_chains[i], false);
  	glLineWidth(1.0f);
}

d2d::Vector TrackChains::getActorStartPos() const
{
	const float x = 200;
	const float r = 100;

	float y = -d2d::FLOAT_MAX;
	for (size_t i = 0, n = m_chains.size(); i < n; ++i)
	{
		for (size_t j = 0, m = m_chains[i].size(); j < m; ++j)
		{
			if (fabs(m_chains[i][j].x - x) < r)
				y = std::max(y, m_chains[i][j].y);
		}
	}

	return d2d::Vector(x, y + 50);
}

void TrackChains::loadFromFile(const std::string& filename)
{	
	loadShapes(filename);
	loadBodies();
}

void TrackChains::loadShapes(const std::string& filename)
{
#ifdef D2D_WINDOWS
	d2d::Resource lResource(filename);
#elif defined D2D_ANDROID_NATIVE
	d2d::Resource lResource(m_pApplication, filename);
#elif defined D2D_ANDROID_JNI
	d2d::Resource lResource(filename);
#endif

	if (lResource.open() != d2d::STATUS_OK)
		assert(0);

	const void *buffer = lResource.bufferize();
	assert(buffer);

 	m_chains.clear();
 
 	byte* ptr = static_cast<byte*>(const_cast<void*>(buffer));
 
 	size_t chainSize = 0;
 	memcpy(&chainSize, ptr, sizeof(size_t));
 	ptr += sizeof(size_t);
 	m_chains.reserve(chainSize);
 	for (size_t i = 0; i < chainSize; ++i)
 	{
		std::vector<d2d::Vector> chain;
 		size_t posSize = 0;
 		memcpy(&posSize, ptr, sizeof(size_t));
 		ptr += sizeof(size_t);
 		chain.reserve(posSize);
 		for (size_t j = 0; j < posSize; ++j)
 		{
 			int x = 0, y = 0;
 			memcpy(&x, ptr, sizeof(int));
 			ptr += sizeof(int);
 			memcpy(&y, ptr, sizeof(int));
 			ptr += sizeof(int);
			if (!chain.empty() && getDistance(chain.back(), d2d::Vector(x, y)) < 2.0f)
				;
			else
 				chain.push_back(d2d::Vector(x, y));
 		}
 		m_chains.push_back(chain);
 	}

	lResource.close();
}

void TrackChains::loadBodies()
{
	b2World* world = m_physicsService->getWorld();

	b2BodyDef def;
	def.type = b2_staticBody;

	for (size_t i = 0, n = m_chains.size(); i < n; ++i)
	{
		std::vector<b2Vec2> b2Pos;
		b2Pos.reserve(m_chains[i].size());
		for (size_t j = 0, m = m_chains[i].size(); j < m; ++j)
		{
			b2Vec2 pos;

 			pos.x = m_chains[i][j].x / d2d::BOX2D_SCALE_FACTOR;
 			pos.y = m_chains[i][j].y / d2d::BOX2D_SCALE_FACTOR;
			b2Pos.push_back(pos);
		}

		b2Body* body = world->CreateBody(&def);

		b2ChainShape shape;
		shape.CreateChain(&b2Pos[0], m_chains[i].size());

		b2FixtureDef fd;
		fd.shape = &shape;
		fd.density = 1.0f;
		fd.friction = g_trackFriction;

		body->CreateFixture(&fd);

		m_bodies.push_back(body);
	}
}
