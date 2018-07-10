#include "MotoXLevelSpritesAdapter.h"

using namespace FEDITOR;

MotoXLevelSpritesAdapter::~MotoXLevelSpritesAdapter()
{
	for_each(m_layers.begin(), m_layers.end(), DeletePointerFunctor<Layer>());
}

void MotoXLevelSpritesAdapter::load(const std::string& filename)
{
	std::ifstream fin(filename.c_str());

	size_t count;
	fin >> count;
	for (size_t i = 0; i < count; ++i)
	{
		Layer* layer = new Layer;
		layer->load(fin);
		m_layers.push_back(layer);
	}

	fin.close();
}

//////////////////////////////////////////////////////////////////////////
// class MotoXLevelSpritesAdapter::Sprite
//////////////////////////////////////////////////////////////////////////

void MotoXLevelSpritesAdapter::Sprite::load(std::ifstream& fin)
{
	fin >> filename >> position >> angle >> xScale >> yScale >> worldID; 
}

//////////////////////////////////////////////////////////////////////////
// class MotoXLevelSpritesAdapter::Layer
//////////////////////////////////////////////////////////////////////////

MotoXLevelSpritesAdapter::Layer::~Layer()
{
	for_each(sprites.begin(), sprites.end(), DeletePointerFunctor<Sprite>());
}

void MotoXLevelSpritesAdapter::Layer::load(std::ifstream& fin)
{
	size_t count;
	fin >> count;
	for (size_t i = 0; i < count; ++i)
	{
		Sprite* sprite = new Sprite;
		sprite->load(fin);
		sprites.push_back(sprite);
	}
}