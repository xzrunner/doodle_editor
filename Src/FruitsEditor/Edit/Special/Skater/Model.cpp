#include "Model.h"
#include "Blackboard.h"
#include "Utility.h"
#include "Dataset/ChainShape.h"
#include "Dataset/Texture.h"
#include "Dataset/TextureRegion.h"
#include "Dataset/Sprite.h"
#include "Dataset/Layer.h"
#include "Dataset/LayersMgr.h"
#include "Edit/EditComponent/LayersMgrCmpt.h"
#include "File/FileNameParser.h"
#include "File/ImgFileAdapter.h"
#include "File/SkaterFileAdapter.h"

using namespace FEDITOR;
using namespace FEDITOR::SKATER;

Model::Model(const AbstractBlackboard* blackboard)
{
	m_blackboard = static_cast<Blackboard*>(const_cast<AbstractBlackboard*>(blackboard));
	m_layersMgr = NULL;
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
		if (FileNameParser::isType(event.getInfo(), FileNameParser::e_skater))
			loadLevel(event.getInfo());
		break;
	case Blackboard::e_OpenOldVersion:
		fixOldVersionData(event.getInfo());
		break;
	case Blackboard::e_OpenBound:
		addSpritesBound(event.getInfo());
		break;
	case Blackboard::e_SaveLevel:
		saveLevel(event.getInfo() + FileNameParser::getFileExtension(FileNameParser::e_skater) + ".txt");
		break;
	case Blackboard::e_SaveTrack:
		saveTrackToFile();
		break;
	case Blackboard::e_SetTexCoords:
		setSelectionTexCoords();
		break;
	}
}

void Model::setLayersMgrCmpt(LayersMgrCmpt* layersMgr)
{
	m_layersMgr = layersMgr;
}

const BoundsContainer& Model::getBoundsContainer() const
{
	return m_bounds;
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

// 	m_trackLayer = new Layer(Layer::e_middle);
// 	m_layers->addLayer(m_trackLayer);
	m_trackLayer = bgLayer;
	m_trackSprite = new Sprite;
	m_trackLayer->addSprite(m_trackSprite);
}

void Model::saveLevel(const std::string& filename) const
{
	std::ofstream fout(filename.c_str());

	const std::vector<Layer*>& layers = m_layers->getAllLayers();
	size_t count = 0;
	for (size_t i = 0, n = layers.size(); i < n; ++i)
		if (layers[i]->getType() == Layer::e_middle) ++count;

	fout << count << '\n';
	for (size_t i = 0, n = layers.size(); i < n; ++i)
	{
		if (layers[i]->getType() != Layer::e_middle) 
			continue;

	 	Layer* layer = layers[i];
	 	const std::vector<Sprite*>& sprites = layer->getAllSprites();
	 	fout << sprites.size() << '\n';
	 	for (size_t i = 0, n = sprites.size(); i < n; ++i)
	 	{
	 		Sprite* sprite = sprites[i];
			float* data = static_cast<float*>(sprite->getUserData());
	 		fout << sprite->getFilename() << " " 
	 			<< sprite->getPosition() << " " 
	 			<< sprite->getAngle() << " "
				<< sprite->getXScale() << " " << sprite->getYScale() << " "
				<< data[0] << " " << data[1] << " " << data[2] << " " << data[3]
	 			<< '\n';
	 	}
	}

	fout.close();
}

void Model::loadLevel(const std::string& filename)
{
	// clear exist layers
	const std::vector<Layer*>& layers = m_layers->getAllLayers();
	while (true) 
	{
		size_t i = 0, n = layers.size();
		for ( ; i < n; ++i)
		{
			if (layers[i]->getType() == Layer::e_middle) 
			{
				m_layers->deleteLayer(i);
				break;
			}
		}
		if (i == n) break;
	}
	m_layersMgr->reloadLayers();

	// add layers
	SkaterFileAdapter sfa;
	sfa.load(filename);
	for (size_t i = 0, n = sfa.m_data.size(); i < n; ++i)
	{
		Layer* layer = new Layer(Layer::e_middle);

		SkaterFileAdapter::Batch* batch = sfa.m_data[i];
		for (size_t j = 0, m = batch->entries.size(); j < m; ++j)
		{
			Sprite* sprite = new Sprite;
			SkaterFileAdapter::Entry* entry = batch->entries[j];
			sprite->setScale(entry->xScale, entry->yScale);
			sprite->loadFromUnknownFile(entry->filename);
			sprite->setTransform(entry->pos, entry->angle);
			float* data = new float[4];
			data[0] = entry->leftLow.x;
			data[1] = entry->leftLow.y;
			data[2] = entry->rightTop.x;
			data[3] = entry->rightTop.y;
			sprite->setUserData(data);
			resetSpriteTexRegions(sprite);
			layer->addSprite(sprite);
		}

		m_layersMgr->addLayer(layer);
	}

	// set editable layer
	m_layersMgr->pushEvent(Event(LayersMgrCmpt::UICtrls::e_SetLayerEditable));
}

void Model::fixOldVersionData(const std::string& filename) const
{
	struct Entry
	{
		std::string name;
		f2Vec2 pos;
		float angle;
	};

	std::vector<Entry> oldData;
	std::ifstream fin(filename.c_str());
	size_t size;
	fin >> size;
	for (size_t i = 0; i < size; ++i)
	{
		Entry entry;
		fin >> entry.name >> entry.pos >> entry.angle;
		oldData.push_back(entry);
	}
	fin.close();

	std::string newFilename = filename.substr(0, filename.find_last_of('.')) + FileNameParser::getFileExtension(FileNameParser::e_skater) + ".txt";
	std::ofstream fout(newFilename.c_str());
	fout << "1" << "\n"
		<< size << "\n";
	for (size_t i = 0, n = oldData.size(); i < n; ++i)
	{
		const Entry& entry(oldData[i]);
		fout << entry.name << " " << entry.pos << " " << entry.angle << " 1 1 0 0 1 1" << "\n";
	}
	fout.close();
}

void Model::setSelectionTexCoords()
{
	const std::set<Sprite*>& sprites = m_layers->getSelection().getAll();
	std::set<Sprite*>::const_iterator itr = sprites.begin();
	for ( ; itr != sprites.end(); ++itr)
	{
		Sprite* sprite = *itr;

		float* data = static_cast<float*>(sprite->getUserData());
		data[0] = m_blackboard->m_texCoordLeft;
		data[1] = m_blackboard->m_texCoordDown,
		data[2] = m_blackboard->m_texCoordRight,
		data[3] = m_blackboard->m_texCoordUp;

		resetSpriteTexRegions(sprite);
	}
}

void Model::resetSpriteTexRegions(Sprite* sprite)
{
	sprite->clearTextureRegions();

	Texture* texture = sprite->getTexture();
	const float hWidth = texture->getWidth() * 0.5f,
		hHeight = texture->getHeight() * 0.5f;

	float* data = static_cast<float*>(sprite->getUserData());
	const float srcLeft = data[0],
		srcRight = data[2],
		srcDown = data[1],
		srcUp = data[3];
	const float dstLeft = -hWidth + texture->getWidth() * srcLeft,
		dstRight = -hWidth + texture->getWidth() * srcRight,
		dstDown = -hHeight + texture->getHeight() * srcDown,
		dstUp = -hHeight + texture->getHeight() * srcUp;

	TextureRegion* rightDown = new TextureRegion;
	rightDown->filename = texture->getFilename();
	rightDown->srcRegion[0].set(srcLeft,	srcDown);
	rightDown->srcRegion[1].set(srcRight,	srcDown);
	rightDown->srcRegion[2].set(srcRight,	srcUp);
	rightDown->dstRegion[0].set(dstLeft,	dstDown);
	rightDown->dstRegion[1].set(dstRight,	dstDown);
	rightDown->dstRegion[2].set(dstRight,	dstUp);
	sprite->pushTextureRegion(rightDown);

	TextureRegion* leftUp = new TextureRegion;
	leftUp->filename = texture->getFilename();
	leftUp->srcRegion[0].set(srcLeft,	srcDown);
	leftUp->srcRegion[1].set(srcRight,	srcUp);
	leftUp->srcRegion[2].set(srcLeft,	srcUp);
	leftUp->dstRegion[0].set(dstLeft,	dstDown);
	leftUp->dstRegion[1].set(dstRight,	dstUp);
	leftUp->dstRegion[2].set(dstLeft,	dstUp);
	sprite->pushTextureRegion(leftUp);
}

void Model::addSpritesBound(const std::string& filename)
{
	m_bounds.insert(filename);

	const std::vector<Layer*>& layers = m_layers->getAllLayers();
	for (size_t i = 0, n = layers.size(); i < n; ++i)
	{
		const std::vector<Sprite*>& sprites = layers[i]->getAllSprites();
		for (size_t j = 0, m = sprites.size(); j < m; ++j)
			Utility::addSpriteBound(sprites[j], m_bounds);
	}
}

void Model::saveTrackToFile()
{
	const std::string filename = 
		"Skater_track" + 
		FileNameParser::getFileExtension(FileNameParser::e_loops) + 
		".txt";
	std::ofstream fout(filename.c_str());

	const std::vector<Shape*>& shapes = m_trackSprite->getAllShapes();
	fout << shapes.size() << '\n';
	for (size_t i = 0, n = shapes.size(); i < n; ++i)
	{
		ChainShape* shape = dynamic_cast<ChainShape*>(shapes[i]);
		assert(shape && shape->m_isLoop);

		fout << shape->m_vertices.size() << '\n';
		for (size_t i = 0, n = shape->m_vertices.size(); i < n; ++i)
		{
			const f2Vec2& pos = shape->m_vertices[i];
			fout << pos << " ";
		}

//		shape->storeToTextFile(fout);
	}

	fout.close();
}