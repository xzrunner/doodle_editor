#include "Level.h"
#include "Background.h"
#include "TrackChains.h"
#include "GroundSurface.h"
#include "SceneTiles.h"
#include "SceneObstacles3.h"

using namespace motox;

Level::Level(d2d::Context* pContext, int scene, int level,
			 ContactListener& contactListener)
	: m_pContext(pContext)
	, m_scene(scene)
	, m_level(level)
	, m_contactListener(contactListener)
	, m_background(NULL)
	, m_track(NULL)
	, m_surface(NULL)
	, m_tiles(NULL)
	, m_obstacles(NULL)
{
}

Level::~Level()
{
	delete m_obstacles;
	delete m_tiles;
	delete m_surface;
	delete m_track;
	delete m_background;
}

void Level::load()
{
//	loadGround();

 	m_background = new Background(m_pContext);
 	m_track = new TrackChains(m_pContext, m_scene, m_level);
 	m_surface = new GroundSurface(m_pContext, m_scene, m_level);
 	m_tiles = new SceneTiles(m_pContext, m_scene, m_level);
 	m_obstacles = new SceneObstacles3(m_pContext, m_scene, m_level, m_contactListener);
}

void Level::update(const d2d::Vector& center)
{
	if (m_background) m_background->update(center);
	if (m_surface) m_surface->update(center);
	if (m_tiles) m_tiles->update(center);
	if (m_obstacles) m_obstacles->update(center);
}

void Level::draw() const
{
	if (m_background) m_background->draw();
//	if (m_track) m_track->draw();
	if (m_surface) m_surface->draw();
	if (m_tiles) m_tiles->draw();
	if (m_obstacles) m_obstacles->draw();
}

d2d::Vector Level::getActorStartPos() const
{
	if (m_track)
		return m_track->getActorStartPos();
	else
		return d2d::Vector();
}

void Level::loadGround()
{
	b2BodyDef def;
	def.type = b2_staticBody;

	b2Body* body = m_pContext->m_physicsService->getWorld()->CreateBody(&def);

	std::vector<b2Vec2> vertices;
	vertices.push_back(b2Vec2(-1000, -100));
	vertices.push_back(b2Vec2( 1000, -100));
	vertices.push_back(b2Vec2( 1000,  100));
	vertices.push_back(b2Vec2(-1000,  100));

	b2ChainShape shape;
	shape.CreateLoop(&vertices[0], vertices.size());

	body->CreateFixture(&shape, 1.0f);
}