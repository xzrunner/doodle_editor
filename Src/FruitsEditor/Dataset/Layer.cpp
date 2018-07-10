#include "Layer.h"
#include "Sprite.h"

using namespace FEDITOR;

Layer::Layer(Type type)
{
	m_visible = true;
	m_type = type;
	m_offset.set(0, 0);
}

Layer::Layer(Type type, const std::string& name)
	: m_name(name)
{
	m_visible = true;
	m_type = type;
	m_offset.set(0, 0);
}

Layer::~Layer()
{
	clearSprites();
}

void Layer::loadFromTextFile(std::ifstream& fin)
{
	for_each(m_sprites.begin(), m_sprites.end(), DeletePointerFunctor<Sprite>());
	m_sprites.clear();

	size_t size;
	fin >> size;
	m_sprites.reserve(size);
	for (size_t i = 0; i < size; ++i)
	{
		Sprite* sprite = new Sprite;
		sprite->loadFromTextFile(fin);
		m_sprites.push_back(sprite);
	}
}

void Layer::storeToTextFile(std::ofstream& fout) const
{
	fout << m_sprites.size();
	for (size_t i = 0, n = m_sprites.size(); i < n; ++i)
		m_sprites[i]->storeToTextFile(fout);
}

bool Layer::deleteSprite(Sprite* sprite)
{
	bool ret = removeSprite(sprite);
	if (ret) delete sprite;
	return ret;
}

bool Layer::removeSprite(Sprite* sprite)
{
	for (size_t i = 0, n = m_sprites.size(); i < n; ++i)
	{
		if (m_sprites[i] == sprite)
		{
			m_sprites.erase(m_sprites.begin() + i);
			return true;
		}
	}
	return false;
}

void Layer::clearSprites()
{
	for_each(m_sprites.begin(), m_sprites.end(), DeletePointerFunctor<Sprite>());
	m_sprites.clear();
}

Sprite* Layer::queryByPos(const f2Vec2& pos, bool isAccurate/* = false*/) const
{
	for (size_t i = 0, n = m_sprites.size(); i < n; ++i)
	{
		if (m_sprites[i]->isContain(pos, isAccurate))
			return m_sprites[i];
	}
	return NULL;
}

void Layer::queryByAABB(const f2AABB& aabb, std::vector<Sprite*>& sprites) const
{
	for (size_t i = 0, n = m_sprites.size(); i < n; ++i)
	{
		if (m_sprites[i]->isIntersect(aabb))
			sprites.push_back(m_sprites[i]);
	}
}

void Layer::updateEachFrame()
{
	for (size_t i = 0, n = m_sprites.size(); i < n; ++i)
		m_sprites[i]->updateEachFrame();
}