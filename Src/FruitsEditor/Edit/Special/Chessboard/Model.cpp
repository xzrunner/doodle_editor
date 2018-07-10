#include "Model.h"
#include "Blackboard.h"
#include "Dataset/ChainShape.h"
#include "Dataset/Sprite.h"
#include "Dataset/Layer.h"
#include "Dataset/LayersMgr.h"

using namespace FEDITOR;
using namespace FEDITOR::CHESSBOARD;

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
		saveLevel(StringTools::intToString(rand()) + "_tilechess.txt");
		break;
	case Blackboard::e_openLevel:
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

	float width = m_blackboard->m_edge * m_blackboard->m_col;
	for (int i = 0; i <= m_blackboard->m_row; ++i)
	{
		ChainShape* line = new ChainShape;
		float y = m_blackboard->m_edge * i;
		line->pushBack(f2Vec2(0.0f, y));
		line->pushBack(f2Vec2(width, y));
		m_bgSprite->pushShape(line);
	}

	float height = m_blackboard->m_edge * m_blackboard->m_row;
	for (int i = 0; i <= m_blackboard->m_col; ++i)
	{
		ChainShape* line = new ChainShape;
		float x = m_blackboard->m_edge * i;
		line->pushBack(f2Vec2(x, 0.0f));
		line->pushBack(f2Vec2(x, height));
		m_bgSprite->pushShape(line);
	}
}

void Model::reloadTileSprites()
{
	Layer* layer = m_layers->getLayer(Layer::e_middle);
	const std::vector<Sprite*>& sprites = layer->getAllSprites();
	for (size_t i = 0, n = sprites.size(); i < n; ++i)
	{
		Sprite* sprite = sprites[i];
		int* data = static_cast<int*>(sprite->getUserData());
		const int col = data[0], row = data[1];
		const float x = col * m_blackboard->m_edge + m_blackboard->m_edge * 0.5f,
			y = row * m_blackboard->m_edge + m_blackboard->m_edge * 0.5f;
		sprite->setTransform(f2Vec2(x, y), 0);
	}
}

void Model::saveLevel(const std::string& filename) const
{
	std::ofstream fout(filename.c_str());

	Layer* layer = m_layers->getLayer(Layer::e_middle);
	const std::vector<Sprite*>& sprites = layer->getAllSprites();
	fout << sprites.size() << '\n';
	for (size_t i = 0, n = sprites.size(); i < n; ++i)
	{
		Sprite* sprite = sprites[i];
		int* data = static_cast<int*>(sprite->getUserData());
		fout << sprite->getFilename() << " " << data[0] << " " << data[1] << '\n';
	}

	fout.close();
}

void Model::loadLevel(const std::string& filename)
{
	std::ifstream fin(filename.c_str());

	Layer* layer = m_layers->getLayer(Layer::e_middle);
	layer->clearSprites();
	size_t size;
	fin >> size;
	for (size_t i = 0; i < size; ++i)
	{
		std::string name;
		int col, row;
		fin >> name >> col >> row;

		Sprite* sprite = new Sprite;
		sprite->loadFromUnknownFile(name);
		const float x = col * m_blackboard->m_edge + m_blackboard->m_edge * 0.5f,
			y = row * m_blackboard->m_edge + m_blackboard->m_edge * 0.5f;

		int* data = new int[2];
		data[0] = col;
		data[1] = row;
		sprite->setUserData(data);

		sprite->setTransform(f2Vec2(x, y), 0);

		layer->addSprite(sprite);
	}
	
	fin.close();
}