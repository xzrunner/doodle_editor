#include "TileFileAdapter.h"

#include <Frame/defs.h>

using namespace deditor::motox;

TileFileAdapter::TileFileAdapter()
	: m_world(NULL)
	, m_worldReverse(NULL)
{
}

TileFileAdapter::TileFileAdapter(b2World* world, b2World* worldReverse)
	: m_world(world)
	, m_worldReverse(worldReverse)
{
}

TileFileAdapter::~TileFileAdapter()
{
	for_each(m_layers.begin(), m_layers.end(), DeletePointerFunctor<Layer>());
	m_layers.clear();
}

void TileFileAdapter::resolve(const wxString& filepath)
{
	std::ifstream fin(filepath.fn_str());

	size_t layerSize;
	fin >> layerSize;
	m_layers.reserve(layerSize);
	for (size_t i = 0; i < layerSize; ++i)
	{
		Layer* layer = new Layer;
		layer->name = StringTools::getLine(fin);
		size_t spriteSize;
		fin >> spriteSize;
		layer->sprites.reserve(spriteSize);
		for (size_t j = 0; j < spriteSize; ++j)
		{
			std::string filename = StringTools::getLine(fin);
			filename = wxgui::FilenameTools::getExistFilepath(filename);

			std::string strLine = StringTools::getLine(fin);
			std::stringstream ss(strLine);

			SpriteDef def;
			ss >> def.pos >> def.angle >> def.scale >> def.type >> def.xMirror >> def.yMirror;

			wxgui::ISprite* sprite = NULL;
			if (wxgui::FilenameTools::getFilename(filename).find(FILLING_POLYGON_TASK_TAG) != wxNOT_FOUND)
				resolveShapeSprite(filename, def, sprite);
			else
				resolveImageSprite(filename, def, sprite);

			wxgui::CombinationSprite* cSprite = dynamic_cast<wxgui::CombinationSprite*>(sprite);
			if (cSprite)
			{
				const std::vector<wxgui::ISprite*>& children = cSprite->getSymbol().getChildren();
				for (size_t i = 0, n = children.size(); i < n; ++i)
				{
					wxgui::ISprite* src = children[i];
					wxgui::ISprite* dst = src->clone();

					bool xMirror, yMirror;
					src->getMirror(xMirror, yMirror);

					dst->setScale(sprite->getScale() * src->getScale());
					dst->setMirror(xMirror, yMirror);

					f2Vec2 location = sprite->getPosition() 
						+ f2Math::rotateVector(src->getPosition() * sprite->getScale(), sprite->getAngle());
					dst->setTransform(location, sprite->getAngle() + src->getAngle());

					layer->sprites.push_back(dst);
				}

				sprite->release();
			}
			else
				layer->sprites.push_back(sprite);
		}
		m_layers.push_back(layer);
	}

	fin.close();
}

void TileFileAdapter::resolveShapeSprite(const std::string& filename, 
										 const SpriteDef& def, wxgui::ISprite*& sprite)
{
	wxgui::ISymbol* symbol = wxgui::SymbolMgr::Instance()->getSymbol(filename);
	sprite = wxgui::SpriteFactory::create(symbol);

	sprite->setTransform(def.pos, def.angle);
	sprite->setScale(def.scale);
	sprite->setMirror(def.xMirror, def.yMirror);
}

void TileFileAdapter::resolveImageSprite(const std::string& filename, 
										  const SpriteDef& def, wxgui::ISprite*& sprite)
{
	wxgui::ISymbol* symbol = wxgui::SymbolMgr::Instance()->getSymbol(filename);
	if (m_world && m_worldReverse)
	{
		switch (def.type)
		{
		case e_image:
			sprite = wxgui::SpriteFactory::create(symbol);
			sprite->setTransform(def.pos, def.angle);
			break;
		case e_physics: case e_physics_static:
			wxgui::BodyFactory::setWorld(m_world);
			sprite = wxgui::SpriteFactory::create(symbol);
			sprite->setTransform(def.pos, def.angle);
			sprite->loadBodyFromFile();
			break;
		case e_physics_reverse: case e_physics_reverse_static:
			wxgui::BodyFactory::setWorld(m_worldReverse);
			sprite = wxgui::SpriteFactory::create(symbol);
			sprite->setTransform(def.pos, def.angle);
			sprite->loadBodyFromFile();
			break;
		}
		if (def.type == e_physics_static || def.type == e_physics_reverse_static)
			sprite->getBody()->getBody()->SetType(b2_staticBody);
	}
	else
	{
		sprite = wxgui::SpriteFactory::create(symbol);
		sprite->setTransform(def.pos, def.angle);
	}

	sprite->setScale(def.scale);
	sprite->setMirror(def.xMirror, def.yMirror);
}