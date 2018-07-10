#include "Model.h"
#include "Blackboard.h"
#include "Strategy.h"
#include "Dataset/ChainShape.h"
#include "Dataset/Texture.h"
#include "Dataset/Sprite.h"
#include "Dataset/Layer.h"
#include "Dataset/LayersMgr.h"
#include "Tools/LibJpeg.h"
#include "SOIL/SOIL.h"
#include "SOIL/stb_image_write.h"

using namespace FEDITOR;
using namespace FEDITOR::TEXTURE_MERGE;

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
	case Blackboard::e_resetBg:
		initBgLinesSprite(m_bgLines);
		break;
	case Blackboard::e_openTexture:
		addTexture(event.getInfo());
		break;
	case Blackboard::e_saveAsBmp:
		saveTextures("composed", BMP);
		break;
	case Blackboard::e_saveAsJpg:
		saveTextures("composed", JPG);
		break;
	case Blackboard::e_saveAsPng:
		saveTextures("composed", PNG);
		break;
	}
}

Layer* Model::getEditedLayer() const
{
	return m_editedLayer;
}

void Model::deleteTexture(Sprite* sprite)
{
	std::vector<Sprite*>::iterator itr = m_textures.begin();
	for ( ; itr != m_textures.end(); ++itr)
	{
		if (*itr == sprite)
		{
			m_textures.erase(itr);
			break;
		}
	}

	BinaryTreeStrategy strategy;

	int width, height;
	m_blackboard->getBgSize(width, height);
	strategy.arrangeTextures(m_textures, width, height);
}

void Model::initLayers()
{
	Layer* bgLayer = new Layer(Layer::e_lowermost);
	bgLayer->m_style.m_chainStyle.color = f2Colorf(0.7f, 0.7f, 0.7f); 
	bgLayer->m_style.m_chainStyle.size = 1.0f;
	bgLayer->m_style.m_bDrawCtlPos = false;

	Sprite* coordsLines = new Sprite;
	initCoordsLinesSprite(coordsLines);
	bgLayer->addSprite(coordsLines);
	m_bgLines = new Sprite;
	initBgLinesSprite(m_bgLines);
	bgLayer->addSprite(m_bgLines);
	m_layers->addLayer(bgLayer);

	m_editedLayer = new Layer(Layer::e_middle);
	m_editedLayer->m_style.m_bDrawAABB = true;
	m_layers->addLayer(m_editedLayer);

	Layer* tmpLayer = new Layer(Layer::e_uppermost);
	m_layers->addLayer(tmpLayer);
}

void Model::initCoordsLinesSprite(Sprite* sprite)
{
	sprite->clearShapes();

	ChainShape* hor = new ChainShape;
	hor->m_vertices.push_back(f2Vec2(-100, 0));
	hor->m_vertices.push_back(f2Vec2(1050, 0));
	sprite->pushShape(hor);

	ChainShape* ver = new ChainShape;
	ver->m_vertices.push_back(f2Vec2(0, -100));
	ver->m_vertices.push_back(f2Vec2(0, 1050));
	sprite->pushShape(ver);
}

void Model::initBgLinesSprite(Sprite* sprite)
{
	sprite->clearShapes();

	int width, height;
	m_blackboard->getBgSize(width, height);
	for (size_t i = 0; i < height; ++i)
	{
		ChainShape* hor = new ChainShape;
		hor->m_vertices.push_back(f2Vec2(0, i + 1));
		hor->m_vertices.push_back(f2Vec2(width, i + 1));
		sprite->pushShape(hor);
	}
	for (size_t i = 0; i < width; ++i)
	{
		ChainShape* ver = new ChainShape;
		ver->m_vertices.push_back(f2Vec2(i + 1, 0));
		ver->m_vertices.push_back(f2Vec2(i + 1, height));
		sprite->pushShape(ver);
	}
}

void Model::addTexture(const std::string& filename)
{
	Sprite* sprite = new Sprite;
	sprite->loadFromUnknownFile(filename);
	m_editedLayer->addSprite(sprite);

	BinaryTreeStrategy strategy;
	m_textures.push_back(sprite);

	int width, height;
	m_blackboard->getBgSize(width, height);
	strategy.arrangeTextures(m_textures, width, height);
}

void Model::saveTextures(const std::string& filename, IMG_TYPE format) const
{
	if (format != BMP && format != PNG && format != JPG) return;

	int width, height;
	m_blackboard->getBgSize(width, height);

	int channel = 4;
	if (format == BMP || format == JPG) channel = 3;
	unsigned char* dst_data = (unsigned char*) malloc(channel * width * height);
	memset(dst_data, 0, channel * width * height);

	for (size_t i = 0, n = m_textures.size(); i < n; ++i)
	{
		Sprite* sprite = m_textures[i];
		const f2Vec2& center = sprite->getPosition();
		Texture* texture = m_textures[i]->getTexture();

		int w, h, c;
		unsigned char* src_data = SOIL_load_image(texture->getFilename().c_str(), &w, &h, &c, 0);
		for (size_t iRow = 0; iRow < h; ++iRow) {
			for (size_t iCol = 0; iCol < w; ++iCol) {
				const int baseFrom = (iRow * w + iCol) * c,
					baseTo = ((height - center.y - h * 0.5f + iRow) * width + center.x - w * 0.5f + iCol) * channel;
				for (size_t iCanel = 0; iCanel < channel; ++iCanel)
					dst_data[baseTo + iCanel] = src_data[baseFrom + iCanel];
			}
		}

		delete[] src_data;
	}

	switch (format) {
		case BMP:
			stbi_write_bmp((filename + ".bmp").c_str(), width, height, channel, dst_data);
			saveComposeInfo((filename + "_bmp.txt").c_str(), height);
			break;
		case PNG:
			stbi_write_png((filename + ".png").c_str(), width, height, channel, dst_data, 0);
			saveComposeInfo((filename + "_png.txt").c_str(), height);
			break;
		case JPG:
			LibJpeg::write_JPEG_file((filename + ".jpg").c_str(), width, height, 80, dst_data);
			saveComposeInfo((filename + "_jpg.txt").c_str(), height);
			break;
	}

	free((void*)dst_data);
}

void Model::saveComposeInfo(const std::string& file, int height) const
{
	std::ofstream fout(file.c_str());
	fout << m_textures.size() << std::endl;
	for (size_t i = 0, n = m_textures.size(); i < n; ++i) {
		Sprite* sprite = m_textures[i];
		const f2Vec2& center = sprite->getPosition();
		Texture* texture = sprite->getTexture();
		const float hw = texture->getWidth() * 0.5f,
			hh = texture->getHeight() * 0.5f;

		fout << texture->getFilename() << " "
			<< center.x - hw << " " << height - (center.y + hh) << " "
			<< texture->getWidth() << " " << texture->getHeight()
			<< std::endl;
	}
	fout.close();
}