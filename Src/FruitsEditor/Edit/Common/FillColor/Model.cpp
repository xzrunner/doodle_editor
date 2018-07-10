#include "Model.h"
#include "Blackboard.h"
#include "Edit/MotoX/Utility.h"
#include "Dataset/ShapeFactory.h"
#include "Dataset/ChainShape.h"
#include "Dataset/TriangleShape.h"
#include "Dataset/Texture.h"
#include "Dataset/Sprite.h"
#include "Dataset/Layer.h"
#include "Dataset/LayersMgr.h"
#include "File/FileNameParser.h"
#include "File/ImgFileAdapter.h"
#include "File/TrisFileAdapter.h"
#include "File/FillFileAdapter.h"

using namespace FEDITOR;
using namespace FEDITOR::FILL_COLOR;

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
	case Blackboard::e_OpenChains:
		if (FileNameParser::isType(event.getInfo(), FileNameParser::e_chains))
			m_chainsSprite->loadFromUnknownFile(event.getInfo());
		break;
	case Blackboard::e_OpenTris:
		if (FileNameParser::isType(event.getInfo(), FileNameParser::e_tris))
			loadTriShapesFromFile(event.getInfo());
		break;
	case Blackboard::e_OpenImg:
		if (FileNameParser::isType(event.getInfo(), FileNameParser::e_img))
			tileSelectionRegionByImg(event.getInfo());
		break;
	case Blackboard::e_OpenFill:
		if (FileNameParser::isType(event.getInfo(), FileNameParser::e_fill))
			loadFillImgFromFile(event.getInfo());
		break;

	case Blackboard::e_SaveTris:
		storeTriShapesToFile("track" + FileNameParser::getFileExtension(FileNameParser::e_tris) + ".txt");
		break;
	case Blackboard::e_SaveFill:
		storeFillImgToFile("track" + FileNameParser::getFileExtension(FileNameParser::e_fill) + ".txt");
		break;

	case Blackboard::e_SetColor:
		triangulationSelections();
		break;
	}
}

void Model::initLayers()
{
	Layer* lowerLayer = new Layer(Layer::e_lowermost);
	m_chainsSprite = new Sprite;
	lowerLayer->addSprite(m_chainsSprite);
	m_layers->addLayer(lowerLayer);

	m_layers->addLayer(new Layer(Layer::e_middle));

	m_layers->addLayer(new Layer(Layer::e_uppermost));
}

void Model::triangulationSelections()
{
	SelectionSet& selection = m_layers->getSelection();
	const std::set<Sprite*>& sprites = selection.getAll();
	std::set<Sprite*>::const_iterator itr = sprites.begin();
	for ( ; itr != sprites.end(); ++itr)
		triangulationSprite(*itr);
}

void Model::triangulationSprite(Sprite* sprite)
{
	const std::vector<Shape*>& shapes = sprite->getAllShapes();
	for (size_t i = 0, n = shapes.size(); i < n; ++i)
	{
		ChainShape* cs = static_cast<ChainShape*>(shapes[i]);
		if (cs && cs->m_isLoop)
			triangulationShape(sprite, cs);
	}
}

void Model::triangulationShape(Sprite* sprite, ChainShape* chain)
{
	DelaunayTriangulation dt(chain->m_vertices, false);
	std::vector<std::vector<f2Vec2> > tris;
	dt.getAllTrisInRegion(tris, chain->m_vertices);
	for (size_t i = 0, n = tris.size(); i < n; ++i)
	{
		TriangleShape* dst = new TriangleShape;
		for (size_t j = 0; j < 3; ++j)
			dst->m_pos[j] = tris[i][j];
		sprite->pushShape(dst);
	}
}

void Model::storeTriShapesToFile(const std::string& filename) const
{
	std::vector<Layer*> layers;
	getValidLayers(layers);

	std::ofstream fout(filename.c_str());

	fout << layers.size() << '\n';
	for (size_t i = 0, n = layers.size(); i < n; ++i)
	{
		Layer* layer = layers[i];
		f2Colorf color = layer->m_style.m_triangleStyle.color;
		fout << color << '\n';

		std::vector<TriangleShape*> tris;
		getTriShapes(layer, tris);
		fout << tris.size() << '\n';
		for (size_t j = 0, m = tris.size(); j < m; ++j)
			tris[j]->storeToTextFile(fout);
	}

	fout.close();
}

void Model::getValidLayers(std::vector<Layer*>& layers) const
{
	const std::vector<Layer*>& src = m_layers->getAllLayers();
	for (size_t i = 0, n = src.size(); i < n; ++i)
	{
		Layer* layer = src[i];

		if (layer->getType() != Layer::e_middle) continue;

		const std::vector<Sprite*>& sprites = layer->getAllSprites();
		if (sprites.empty()) continue;

		layers.push_back(layer);
	}
}

void Model::getTriShapes(const Layer* layer, std::vector<TriangleShape*>& tris) const
{
	const std::vector<Sprite*>& sprites = layer->getAllSprites();
	for (size_t i = 0, n = sprites.size(); i < n; ++i)
	{
		Sprite* sprite = sprites[i];
		const std::vector<Shape*>& shapes = sprite->getAllShapes();
		for (size_t j = 0, m = shapes.size(); j < m; ++j)
		{
			TriangleShape* tri = dynamic_cast<TriangleShape*>(shapes[j]);
			if (tri) tris.push_back(tri);
		}
	}
}

void Model::loadTriShapesFromFile(const std::string& filename)
{
	TrisFileAdapter fa;
	fa.load(filename);

	for (size_t i = 0, n = fa.m_layers.size(); i < n; ++i)
	{
		TrisFileAdapter::Layer* src = fa.m_layers[i];

		Layer* dst = new Layer(Layer::e_middle);
		dst->m_style.m_triangleStyle.color = src->color;
		for (size_t j = 0, m = src->shapes.size(); j < m; ++j)
		{
			Sprite* sprite = new Sprite;
			sprite->pushShape(src->shapes[j]);
			dst->addSprite(sprite);
		}

		m_layers->addMidLayer(dst);
	}
}

void Model::tileSelectionRegionByImg(const std::string& filename)
{
	Layer* layer = m_layers->getLayer(Layer::e_middle);
	assert(layer);
	layer->m_style.m_bShapeMask = true;

	SelectionSet& selection = m_layers->getSelection();
	const std::set<Sprite*>& sprites = selection.getAll();
	std::set<Sprite*>::const_iterator itr = sprites.begin();
	for ( ; itr != sprites.end(); ++itr)
	{
		const std::vector<Shape*>& shapes = (*itr)->getAllShapes();
		for (size_t i = 0, n = shapes.size(); i < n; ++i)
		{
			ChainShape* cs = dynamic_cast<ChainShape*>(shapes[i]);
			if (cs && cs->m_isLoop)
			{
				triangulationShape(*itr, cs);
				tileLoopByImg(filename, layer, cs);
				m_regions.insert(std::make_pair(cs, filename));
			}
		}
	}
}

void Model::tileLoopByImg(const std::string& filename, Layer* layer, ChainShape* cs)
{
	Texture* tex = TexturesMgr::Instance()->getItem(filename);
	const float width = tex->getWidth() * MOTOX::SCALE_SCREEN_TO_PHYSICS,
		height = tex->getHeight() * MOTOX::SCALE_SCREEN_TO_PHYSICS;

	f2AABB aabb;
	for (size_t i = 0, n = cs->m_vertices.size(); i < n; ++i)
		aabb.combine(cs->m_vertices[i]);

	float x = aabb.xMin,
		y = aabb.yMin;
	while (y < aabb.yMax)
	{
		while (x < aabb.xMax)
		{
			Sprite* sprite = new Sprite(MOTOX::SCALE_SCREEN_TO_PHYSICS);
			ImgFileAdapter fa;
			fa.m_sprite = sprite;
			fa.load(filename);

			sprite->setTransform(f2Vec2(x + width * 0.5f, y + height * 0.5f), 0);
			layer->addSprite(sprite);
			x += width;
		}
		x = aabb.xMin;
		y += height;
	}
}

void Model::storeFillImgToFile(const std::string& filename) const
{
	std::ofstream fout(filename.c_str());

	fout << m_regions.size() << '\n';
	std::map<ChainShape*, std::string>::const_iterator itr = m_regions.begin();
	for ( ; itr != m_regions.end(); ++itr)
	{
		fout << itr->second << '\n';
		itr->first->storeToTextFile(fout);
	}

	fout.close();
}

void Model::loadFillImgFromFile(const std::string& filename)
{
	FillFileAdapter fa;
	fa.load(filename);

	Layer* layer = m_layers->getLayer(Layer::e_middle);
	assert(layer);
	layer->m_style.m_bShapeMask = true;

	for (size_t i = 0, n = fa.m_regions.size(); i < n; ++i)
	{
		FillFileAdapter::Region* region = fa.m_regions[i];

		Sprite* sprite = new Sprite;
		layer->addSprite(sprite);
		sprite->pushShape(region->shape);
		triangulationShape(sprite, region->shape);
		tileLoopByImg(region->filename, layer, region->shape);
	}
}