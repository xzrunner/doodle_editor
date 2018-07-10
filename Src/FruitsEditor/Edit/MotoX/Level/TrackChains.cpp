#include "TrackChains.h"
#include "TypesDef.h"
#include "../../../Dataset/BodyFactory.h"
#include "../../../Dataset/BodyData.h"
#include "../../../Dataset/ChainBody.h"
#include "../../../Dataset/ChainShape.h"
#include "../../../Dataset/Sprite.h"
#include "../../../Dataset/Layer.h"
#include "../../../Dataset/LayersMgr.h"
#include "../../../File/FileNameParser.h"
#include "../../../File/ChainsFileAdapter.h"

using namespace FEDITOR;
using namespace FEDITOR::MOTOX::LEVEL;

TrackChains::TrackChains(b2World* world, b2World* worldReverse)
{
	m_world = world;
	m_worldReverse = worldReverse;

	m_phys = NULL;
	m_physReverse = NULL;
	m_shapes = NULL;
}

void TrackChains::initialize(LayersMgr* layersMgr)
{
	m_layer = new Layer(Layer::e_middle, "track_chains");

	m_layer->m_style.m_chainStyle.color = f2Colorf(0, 0, 0);
	m_layer->m_style.m_chainStyle.size = 3;
	m_layer->m_style.m_bDrawCtlPos = false;

	m_phys = new Sprite;
	m_physReverse = new Sprite;
	m_shapes = new Sprite;
	m_layer->addSprite(m_phys);
	m_layer->addSprite(m_physReverse);
	m_layer->addSprite(m_shapes);

	layersMgr->addLayer(m_layer);
}

void TrackChains::loadFromFile(const std::string& filename, b2World* world, b2World* worldReverse)
{
	if (FileNameParser::isType(filename, FileNameParser::e_chains))
	{
		m_phys->setBody(BodyFactory::createBody(filename));

		BodyFactory::setWorld(worldReverse);
		m_physReverse->setBody(BodyFactory::createBody(filename));
		BodyFactory::setWorld(world);

		setBodyType();

		ChainsFileAdapter fa;
		fa.load(filename);
		for (size_t i = 0, n = fa.m_chains.size(); i < n; ++i)
			m_shapes->pushShape(fa.m_chains[i]->clone());
	}
}

void TrackChains::storeToFile(const std::string& filename) const
{
	std::ofstream fout(filename.c_str());

	const std::vector<Shape*>& shapes = m_shapes->getAllShapes();
	fout << shapes.size() << '\n';
	for (size_t i = 0, n = shapes.size(); i < n; ++i)
		shapes[i]->storeToTextFile(fout);

	fout.close();
}

void TrackChains::setCtlposDrawable(bool draw)
{
	m_layer->m_style.m_bDrawCtlPos = draw;
}

Sprite* TrackChains::getShapeSprite() const
{
	return m_shapes;
}

void TrackChains::addFixtureFromLastChain()
{
	if (m_shapes->getAllShapes().empty()) return;

	b2ChainShape shape;
	createShapeFromChain(m_shapes->getAllShapes().back(), shape);

	b2FixtureDef fd;
	fd.shape = &shape;
	fd.density = 1.0f;

	BodyData* bodyData = NULL;
	Body* body = m_phys->getBody();
	if (body) bodyData = BodyDataMgr::Instance()->getItem(body->getFilename());

	if (bodyData)
	{
		assert(!bodyData->getAllFixturesData().empty());
		BodyData::FixtureData* fixtureData = bodyData->getAllFixturesData().back();
		fixtureData->setFixtureDef(fd);
	}
	else
	{
		if (!body)
		{
			m_phys->setBody(new ChainBody(m_world));
			m_physReverse->setBody(new ChainBody(m_worldReverse));
			setBodyType();
		}
	}

	m_phys->getBody()->getBody()->CreateFixture(&fd);
	m_physReverse->getBody()->getBody()->CreateFixture(&fd);
}

void TrackChains::createPhysFromAllChains()
{
	assert(m_phys && m_phys->getBody() && m_phys->getBody()->getBody());

	const float friction = m_phys->getBody()->getBody()->GetFixtureList()->GetFriction(),
		frictionReverse = m_physReverse->getBody()->getBody()->GetFixtureList()->GetFriction();
	m_phys->setBody(new ChainBody(m_world));
	m_physReverse->setBody(new ChainBody(m_worldReverse));
	setBodyType();

	b2FixtureDef fd, fdReverse;
	fd.friction = friction;
	fdReverse.friction = frictionReverse;

	const std::vector<Shape*>& shapes = m_shapes->getAllShapes();
	for (size_t i = 0, n = shapes.size(); i < n; ++i)
	{
		b2ChainShape shape;
		createShapeFromChain(shapes[i], shape);
		fd.shape = &shape;
		fdReverse.shape = &shape;

		m_phys->getBody()->getBody()->CreateFixture(&fd);
		m_physReverse->getBody()->getBody()->CreateFixture(&fdReverse);
	}
}

b2Body* TrackChains::getBody() const
{
	if (m_phys && m_phys->getBody())
		return m_phys->getBody()->getBody();
	else
		return NULL;
}

b2Body* TrackChains::getReverseBody() const
{
	if (m_physReverse && m_physReverse->getBody())
		return m_physReverse->getBody()->getBody();
	else
		return NULL;
}

void TrackChains::setFriction(float friction)
{
	m_phys->getBody()->setFriction(friction);
}

void TrackChains::createShapeFromChain(Shape* shape, b2ChainShape& b2Shape)
{
	ChainShape* chainShape = dynamic_cast<ChainShape*>(shape);
	assert(chainShape);

	std::vector<b2Vec2> b2Pos;
	b2Pos.reserve(chainShape->m_vertices.size());
	for (size_t i = 0, n = chainShape->m_vertices.size(); i < n; ++i)
	{
		b2Vec2 p;
		p.x = chainShape->m_vertices[i].x;
		p.y = chainShape->m_vertices[i].y;
		b2Pos.push_back(p);
	}
	b2Shape.CreateChain(&b2Pos[0], b2Pos.size());
}

void TrackChains::setBodyType()
{
	int* type = new int;
	*type = e_TrackChain;

	m_phys->getBody()->getBody()->SetUserData(type);
	m_physReverse->getBody()->getBody()->SetUserData(type);
}