#include "Model.h"
#include "Blackboard.h"
#include "../Utility.h"
#include "../Actor.h"
#include "../../../Dataset/ChainShape.h"
#include "../../../Dataset/BodyFactory.h"
#include "../../../Dataset/Sprite.h"
#include "../../../Dataset/Layer.h"
#include "../../../Dataset/LayersMgr.h"
#include "../../../File/FileNameParser.h"
#include "../../../File/ImgFileAdapter.h"
#include "../../../File/MotoXLevelSpritesAdapter.h"
#include <Box2D/Box2D.h>

using namespace FEDITOR;
using namespace FEDITOR::MOTOX::LEVEL;

Model::Model(const AbstractBlackboard* blackboard, b2World* world, b2World* worldReverse)
	: m_trackChains(world, worldReverse)
{
	m_blackboard = static_cast<Blackboard*>(const_cast<AbstractBlackboard*>(blackboard));
	m_world = world;
	m_worldReverse = worldReverse;

	initLayers();
	initBgSprites();

	m_actor = NULL;
}

Model::~Model()
{

}

void Model::handleEvent(const Event& event)
{
	switch (event.getID())
	{
	case Blackboard::e_OpenBgTexture:
		if (FileNameParser::isType(event.getInfo(), FileNameParser::e_img))
		{
			ImgFileAdapter fa;
			fa.m_sprite = m_bgTextureSprite;
			fa.load(event.getInfo());
		}
		break;

	case Blackboard::e_OpenTrackChain:
		m_trackChains.loadFromFile(event.getInfo(), m_world, m_worldReverse);
		break;
	case Blackboard::e_SaveTrackChain:
		m_trackChains.storeToFile("track" + FileNameParser::getFileExtension(FileNameParser::e_chains) + ".txt");
		break;
	case Blackboard::e_SetTrackFriction:
		m_trackChains.setFriction(m_blackboard->m_trackFriction);
		break;

	case Blackboard::e_OpenMotorbike:
		if (m_actor) delete m_actor;
		m_actor = new Actor(m_world, m_actorLayer, event.getInfo());
		initActorParams();
		m_actor->translate(f2Vec2(2, 2));
		break;

	case Blackboard::e_UpdateActor:
		if (m_actor) m_actor->driving();
		break;

	case Blackboard::e_SetMotoFriction:
		if (m_actor) 
			m_actor->setValue(Actor::e_SetWheelFriction, m_blackboard->m_motoFriction);
		break;
	case Blackboard::e_SetMotoDensity:
		if (m_actor) 
			m_actor->setValue(Actor::e_SetMotoDensity, m_blackboard->m_motoDensity);
		break;
	case Blackboard::e_SetPlayerDensity:
		if (m_actor) 
			m_actor->setValue(Actor::e_SetPlayerDensity, m_blackboard->m_motoDensity);
		break;
	case Blackboard::e_SetMotoSpeed:
		if (m_actor) 
			m_actor->setValue(Actor::e_SetSpeed, m_blackboard->m_motoSpeed);
		break;
	case Blackboard::e_SetMotoAcc:
		if (m_actor) 
			m_actor->setValue(Actor::e_SetAcc, m_blackboard->m_motoAcc);
		break;
	case Blackboard::e_SetMotoTorque:
		if (m_actor) 
			m_actor->setValue(Actor::e_SetTorque, m_blackboard->m_motoTorque);
		break;
	case Blackboard::e_SetMotoDamping:
		if (m_actor) 
			m_actor->setValue(Actor::e_SetDamping, m_blackboard->m_motoDamping);
		break;
	case Blackboard::e_SetMotoHz:
		if (m_actor) 
			m_actor->setValue(Actor::e_SetHz, m_blackboard->m_motoHz);
		break;
	case Blackboard::e_SetMotoMaxMotorTorque:
		if (m_actor) 
			m_actor->setValue(Actor::e_SetMaxMotorTorque, m_blackboard->m_motoMaxMotorTorque);
		break;

	case Blackboard::e_SaveSprites:
		storeAllSpritesToFile();
		break;
	case Blackboard::e_OpenAllSprites:
		loadAllSpritesFromFile(event.getInfo());
		break;
	}
}

f2Vec2 Model::getActorPos() const
{
	return m_actor->getCenterPos();
}

void Model::initLayers()
{
	// background
	m_bgLayer = new Layer(Layer::e_lowermost);
	m_bgLayer->m_style.m_bDrawCtlPos = false;
	m_layers->addLayer(m_bgLayer);
	// track chain
	m_trackChains.initialize(m_layers);
	// actor
	m_actorLayer = new Layer(Layer::e_middle, "actor");
	m_layers->addLayer(m_actorLayer);
	// empty
	m_layers->addLayer(new Layer(Layer::e_middle));
	// temp
	Layer* tempLayer = new Layer(Layer::e_uppermost);
	m_layers->addLayer(tempLayer);
}

void Model::initBgSprites()
{
	m_bgTextureSprite = new Sprite(MOTOX::SCALE_SCREEN_TO_PHYSICS);
	f2Vec2 pos;
	pos.x = SCREEN_WIDTH * 0.5f * MOTOX::SCALE_SCREEN_TO_PHYSICS;
	pos.y = SCREEN_HEIGHT * 0.5f * MOTOX::SCALE_SCREEN_TO_PHYSICS;
	m_bgTextureSprite->setTransform(pos, 0);
	m_bgLayer->addSprite(m_bgTextureSprite);

	m_bgShapeSprite = new Sprite;
	m_bgLayer->addSprite(m_bgShapeSprite);

	initBgGridsSprite();
}

void Model::initBgGridsSprite()
{
	const float width = SCREEN_WIDTH * SCALE_SCREEN_TO_PHYSICS,
		height = SCREEN_HEIGHT * SCALE_SCREEN_TO_PHYSICS;

	Sprite* sprite = new Sprite;

	ChainShape* shape = new ChainShape;
	shape->pushBack(f2Vec2(0.0f, 0.0f));
	shape->pushBack(f2Vec2(width * MAX_SCREEN_WIDTH_TIMES, 0.0f));
	shape->pushBack(f2Vec2(width * MAX_SCREEN_WIDTH_TIMES, height));
	shape->pushBack(f2Vec2(0.0f, height));
	sprite->pushShape(shape);
	for (size_t i = 0; i < MAX_SCREEN_WIDTH_TIMES; ++i)
	{
		ChainShape* shape = new ChainShape;
		shape->pushBack(f2Vec2(width * i, 0.0f));
		if (i % DIVIDE_WIDTH_TIMES == 0)
			shape->pushBack(f2Vec2(width * i, height * 2));
		else
			shape->pushBack(f2Vec2(width * i, height));
		sprite->pushShape(shape);
	}

	m_bgLayer->addSprite(sprite);
}

void Model::initActorParams()
{
	handleEvent(Event(Blackboard::e_SetMotoFriction));
	handleEvent(Event(Blackboard::e_SetMotoDensity));
	handleEvent(Event(Blackboard::e_SetPlayerDensity));
	handleEvent(Event(Blackboard::e_SetMotoSpeed));
	handleEvent(Event(Blackboard::e_SetMotoAcc));
	handleEvent(Event(Blackboard::e_SetMotoTorque));
	handleEvent(Event(Blackboard::e_SetMotoDamping));
	handleEvent(Event(Blackboard::e_SetMotoHz));
	handleEvent(Event(Blackboard::e_SetMotoMaxMotorTorque));
}

void Model::storeAllSpritesToFile() const
{
	std::ofstream fout("motox_level_sprites.txt");
	const std::vector<Layer*>& layers = m_layers->getAllLayers();

	size_t count = 0;
	fout << count << '\n';
	for (size_t i = 0, n = layers.size(); i < n; ++i)
	{
		Layer* layer = layers[i];
		const std::string& name = layer->getName();
		if (name.substr(0, name.find_first_of('_')) == "layer")
		{
			const std::vector<Sprite*>& sprites = layer->getAllSprites();
			fout << sprites.size() << '\n';
			for (size_t j = 0, m = sprites.size(); j < m; ++j)
			{
				Sprite* sprite = sprites[j];
				int worldID = 0;
				if (sprite->getBody())
				{
					b2Body* body = sprite->getBody()->getBody();
					if (body->GetWorld() == m_world) worldID = 1;
					else worldID = 2;
				}
				fout << sprite->getFilename() << '\n'
					<< sprite->getPosition() << " " << sprite->getAngle() << " " << sprite->getXScale() << sprite->getYScale() << '\n'
					<< worldID << '\n';
			}
			++count;
		}
	}
	fout.seekp(std::ios_base::beg);
	fout << count/* << '\n'*/;
	fout.close();
}

void Model::loadAllSpritesFromFile(const std::string& filename)
{
	if (!FileNameParser::isType(filename, FileNameParser::e_motoxSprites))
		return;

	Layer* layer = NULL;
	const std::vector<Layer*>& layers = m_layers->getAllLayers();
	for (size_t i = 0, n = layers.size(); i < n; ++i)
	{
		const std::string& name = layers[i]->getName();
		if (name.substr(0, name.find_first_of('_')) == "layer")
		{
			layer = layers[i];
			break;
		}
	}

	assert(layer);
	layer->clearSprites();

	MotoXLevelSpritesAdapter ma;
	ma.load(filename);

	if (ma.m_layers.empty()) return;

	MotoXLevelSpritesAdapter::Layer* layerAdapter = ma.m_layers[0];
	for (size_t i = 0, n = layerAdapter->sprites.size(); i < n; ++i)
	{
		MotoXLevelSpritesAdapter::Sprite* spriteAdapter = layerAdapter->sprites[i];

		if (spriteAdapter->worldID == 1) BodyFactory::setWorld(m_world);
		else if (spriteAdapter->worldID == 2) BodyFactory::setWorld(m_worldReverse);

		Sprite* sprite = new Sprite(fabs(spriteAdapter->xScale));
		sprite->loadFromUnknownFile(spriteAdapter->filename);
		sprite->setTransform(spriteAdapter->position, spriteAdapter->angle);
		sprite->setScale(spriteAdapter->xScale, spriteAdapter->yScale);
		if (sprite->getBody())
			sprite->getBody()->setAlive(true);

		layer->addSprite(sprite);
	}
}

void Model::addToBodySpriteMap(Sprite* sprite)
{
	if (sprite->getBody() && sprite->getBody()->getBody())
		m_mapBodyToSprite.insert(std::make_pair(sprite->getBody()->getBody(), sprite));
}

void Model::eraseFromBodySpriteMap(b2Body* body)
{
	std::map<b2Body*, Sprite*>::const_iterator itr = m_mapBodyToSprite.find(body);
	if (itr != m_mapBodyToSprite.end()) m_mapBodyToSprite.erase(itr);
}

Sprite* Model::querySpriteByBody(b2Body* body) const
{
	std::map<b2Body*, Sprite*>::const_iterator itr = m_mapBodyToSprite.find(body);
	if (itr == m_mapBodyToSprite.end()) return NULL;
	else return itr->second;
}