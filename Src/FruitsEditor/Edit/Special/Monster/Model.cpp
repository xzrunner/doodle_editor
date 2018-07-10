#include "Model.h"
#include "Blackboard.h"
#include "Dataset/ChainShape.h"
#include "Dataset/Sprite.h"
#include "Dataset/Layer.h"
#include "Dataset/LayersMgr.h"
#include "File/MonsterFileAdapter.h"
#include "File/FileNameParser.h"

using namespace FEDITOR;
using namespace FEDITOR::MONSTER;

Model::Model(const AbstractBlackboard* blackboard)
{
	m_blackboard = static_cast<Blackboard*>(const_cast<AbstractBlackboard*>(blackboard));
	initLayers();
}

Model::~Model()
{
}

void Model::handleEvent(const Event& event)
{
	switch (event.getID())
	{
	case Blackboard::e_resizeBg:
		reloadBgSprite();
		reloadTileSprites();
		break;
	case Blackboard::e_saveLevel:
		saveLevel(event.getInfo() + FileNameParser::getFileExtension(FileNameParser::e_monster) + ".txt");
		break;
	case Blackboard::e_openLevel:
		if (FileNameParser::isType(event.getInfo(), FileNameParser::e_monster))
			loadLevel(event.getInfo());
		break;
	}
}

void Model::initLayers()
{
	Layer* bgLayer = new Layer(Layer::e_lowermost);
	bgLayer->m_style.m_bDrawCtlPos = false;
	m_bgSprite = new Sprite;
	reloadBgSprite();
	bgLayer->addSprite(m_bgSprite);
	m_layers->addLayer(bgLayer);

	m_layers->addLayer(new Layer(Layer::e_middle));

	m_layers->addLayer(new Layer(Layer::e_uppermost));
}

void Model::reloadBgSprite()
{
	m_bgSprite->clearShapes();

	ChainShape* divide = new ChainShape;
	divide->pushBack(f2Vec2(- m_blackboard->m_edge * 3.0f, 0.0f));
	divide->pushBack(f2Vec2(  m_blackboard->m_edge * (3.0f + Blackboard::COL), 0.0f));
	m_bgSprite->pushShape(divide);

	// below
	float width = m_blackboard->m_edge * Blackboard::COL;
	for (int i = 0; i <= Blackboard::ROW; ++i)
	{
		ChainShape* line = new ChainShape;
		float y = - m_blackboard->m_edge * i;
		line->pushBack(f2Vec2(0.0f, y));
		line->pushBack(f2Vec2(width, y));
		m_bgSprite->pushShape(line);
	}

	float height = m_blackboard->m_edge * Blackboard::ROW;
	for (int i = 0; i <= Blackboard::COL; ++i)
	{
		ChainShape* line = new ChainShape;
		float x = m_blackboard->m_edge * i;
		line->pushBack(f2Vec2(x, 0.0f));
		line->pushBack(f2Vec2(x, - height));
		m_bgSprite->pushShape(line);
	}

	// above
	height = m_blackboard->m_edge * m_blackboard->m_length;
	for (int i = 0; i <= Blackboard::COL; ++i)
	{
		ChainShape* line = new ChainShape;
		float x = m_blackboard->m_edge * i;
		line->pushBack(f2Vec2(x, 0.0f));
		line->pushBack(f2Vec2(x, height));
		m_bgSprite->pushShape(line);
	}
	ChainShape* top = new ChainShape;
	top->pushBack(f2Vec2(0.0f, height));
	top->pushBack(f2Vec2(width, height));
	m_bgSprite->pushShape(top);

	// Preview
	ChainShape* bound = new ChainShape;
	bound->pushBack(f2Vec2(-960.0f, 0.0f));
	bound->pushBack(f2Vec2(-480.0f, 0.0f));
	bound->pushBack(f2Vec2(-480.0f, 800.0f));
	bound->pushBack(f2Vec2(-960.0f, 800.0f));
	bound->m_isLoop = true;
	m_bgSprite->pushShape(bound);
}

void Model::reloadTileSprites()
{
 	Layer* layer = m_layers->getLayer(Layer::e_middle);
 	const std::vector<Sprite*>& sprites = layer->getAllSprites();
 	for (size_t i = 0, n = sprites.size(); i < n; ++i)
 	{
 		Sprite* sprite = sprites[i];
 		float* data = static_cast<float*>(sprite->getUserData());
 		const float col = data[0], row = data[1];
		const float x = (col - 1) * m_blackboard->m_edge + m_blackboard->m_edge * 0.5f;
		if (row < 0)
		{
			const float y = (row + 1) * m_blackboard->m_edge - m_blackboard->m_edge * 0.5f;
			sprite->setTransform(f2Vec2(x, y), 0);
		}
		else
		{
			const float y = row * (m_blackboard->m_edge * m_blackboard->m_length);
			sprite->setTransform(f2Vec2(x, y), 0);
		} 		
 	}
}

void Model::saveLevel(const std::string& filename) const
{
	std::ofstream fout(filename.c_str());

	fout << m_blackboard->m_time << '\n'
		<< m_blackboard->m_length << '\n'
		<< m_blackboard->m_minEmptyGrid << '\n'
		<< m_blackboard->m_maxEmptyGrid << '\n'
		<< std::endl;

	Layer* layer = m_layers->getLayer(Layer::e_middle);
	const std::vector<Sprite*>& sprites = layer->getAllSprites();
	fout << sprites.size() << '\n';
	for (size_t i = 0, n = sprites.size(); i < n; ++i)
	{
		Sprite* sprite = sprites[i];
		float* data = static_cast<float*>(sprite->getUserData());
		fout << sprite->getFilename() << " " << (int) (data[0] + 0.5f) << " " << data[1] << " " << data[2] << '\n';
	}

	fout.close();
}

void Model::loadLevel(const std::string& filename)
{
	MonsterFileAdapter data;
	data.load(filename);

	m_blackboard->m_time = data.m_time;
	m_blackboard->m_length = data.m_length;
	m_blackboard->m_minEmptyGrid = data.m_minEmptyGrid;
	m_blackboard->m_maxEmptyGrid = data.m_maxEmptyGrid;
 	Layer* layer = m_layers->getLayer(Layer::e_middle);
 	layer->clearSprites();
	for (size_t i = 0, n = data.m_items.size(); i < n; ++i)
	{
		const MonsterFileAdapter::Item& item = data.m_items[i];

 		Sprite* sprite = new Sprite;
 		sprite->loadFromUnknownFile(item.name);
 		const float x = (item.col - 1) * m_blackboard->m_edge + m_blackboard->m_edge * 0.5f;
 		if (item.row < 0)
 		{
 			float y = (item.row + 1) * m_blackboard->m_edge - m_blackboard->m_edge * 0.5f;
 			sprite->setTransform(f2Vec2(x, y), 0);
 		}
 		else
 		{
 			const float y = m_blackboard->m_edge * m_blackboard->m_length * item.row;
 			sprite->setTransform(f2Vec2(x, y), 0);
 		}
 
 		float* data = new float[3];
 		data[0] = item.col;
 		data[1] = item.row;
 		data[2] = item.id;
 		sprite->setUserData(data);
 
 		layer->addSprite(sprite);
	}
}