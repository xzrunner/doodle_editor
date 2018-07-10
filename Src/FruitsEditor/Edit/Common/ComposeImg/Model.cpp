#include "Model.h"
#include "Blackboard.h"
#include "Dataset/Sprite.h"
#include "Dataset/Layer.h"
#include "Dataset/LayersMgr.h"
#include "Dataset/ChainShape.h"
#include "File/FileNameParser.h"
#include "File/ImgFileAdapter.h"
#include "File/ComposeImagesAdapter.h"

using namespace FEDITOR;
using namespace FEDITOR::COMPOSE_IMG;

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
	case Blackboard::e_OpenBackground:
		if (FileNameParser::isType(event.getInfo(), FileNameParser::e_img))
		{
			ImgFileAdapter fa;
			fa.m_sprite = m_bgSprite;
			fa.load(event.getInfo());
		}
		break;
	case Blackboard::e_OpenLevel:
		loadLevel(event.getInfo());
		break;
	case Blackboard::e_SaveLevel:
		saveLevel(event.getInfo() + FileNameParser::getFileExtension(FileNameParser::e_composeImgs) + ".txt");
		break;
	}
}

void Model::initLayers()
{
	Layer* bgLayer = new Layer(Layer::e_lowermost);
	m_bgSprite = new Sprite;
	bgLayer->addSprite(m_bgSprite);
	m_layers->addLayer(bgLayer);

	m_layers->addLayer(new Layer(Layer::e_middle));

	Layer* tempLayer = new Layer(Layer::e_uppermost);
	m_layers->addLayer(tempLayer);
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
		fout << sprite->getFilename() << " " 
			<< sprite->getPosition() << " " 
			<< sprite->getAngle() 
			<< '\n';
	}

	fout.close();
}

void Model::loadLevel(const std::string& filename)
{
	if (!FileNameParser::isType(filename, FileNameParser::e_composeImgs))
		return;

	ComposeImagesAdapter cia;
	cia.load(filename);

	Layer* layer = m_layers->getLayer(Layer::e_middle);
	layer->clearSprites();
	for (size_t i = 0, n = cia.m_entries.size(); i < n; ++i)
	{
		ComposeImagesAdapter::Entry& entry = cia.m_entries[i];
		Sprite* sprite = new Sprite;
		sprite->loadFromUnknownFile(entry.filename);
		sprite->setTransform(f2Vec2(entry.x, entry.y), entry.angle);
		layer->addSprite(sprite);
	}
}