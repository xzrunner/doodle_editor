#include "CombinationSymbol.h"
#include "ISprite.h"
#include "SymbolMgr.h"
#include "SpriteFactory.h"

#include "Tools/CombinationFileAdapter.h"
#include "Render/SpriteDraw.h"

using namespace wxgui;

CombinationSymbol::CombinationSymbol()
{
}

CombinationSymbol::CombinationSymbol(const std::vector<ISprite*>& children)
{
	m_sprites.reserve(children.size());
	for (size_t i = 0, n = children.size(); i < n; ++i)
		m_sprites.push_back(children[i]->clone());
}

CombinationSymbol::~CombinationSymbol()
{
	for (size_t i = 0, n = m_sprites.size(); i < n; ++i)
		m_sprites[i]->release();
}

CombinationSymbol* CombinationSymbol::clone()
{
	return NULL;
}

void CombinationSymbol::loadFromTextFile(std::ifstream& fin)
{

}

void CombinationSymbol::storeToTextFile(std::ofstream& fout) const
{

}

void CombinationSymbol::reloadTexture() const
{
	for (size_t i = 0, n = m_sprites.size(); i < n; ++i)
		m_sprites[i]->getSymbol().reloadTexture();
}

void CombinationSymbol::draw() const
{
	for (size_t i = 0, n = m_sprites.size(); i < n; ++i)
		SpriteDraw::drawSprite(m_sprites[i]);
}

float CombinationSymbol::getWidth() const
{
	return 0;
}

float CombinationSymbol::getHeight() const
{
	return 0;
}

void CombinationSymbol::loadResources()
{
	CombinationFileAdapter adapter;
	adapter.load(m_filepath.c_str());

	for (size_t i = 0, n = adapter.m_data.size(); i < n; ++i)
	{
		ISprite* sprite = NULL;

		const CombinationFileAdapter::Entry& entry = adapter.m_data[i];
		ISymbol* symbol = SymbolMgr::Instance()->getSymbol(entry.filepath);
		sprite = SpriteFactory::create(symbol);

		sprite->setTransform(entry.pos, entry.angle);
		sprite->setScale(entry.scale);
		sprite->setMirror(entry.xMirror, entry.yMirror);

		m_sprites.push_back(sprite);
	}

//	moveToCenter();

	initBounding();
}

void CombinationSymbol::moveToCenter()
{
	for (size_t i = 0, n = m_sprites.size(); i < n; ++i)
	{
		std::vector<f2Vec2> vertices;
		m_sprites[i]->getBounding()->getBoundPos(vertices);
		for (size_t j = 0, m = vertices.size(); j < m; ++j)
			m_bounding.combine(vertices[j]);
	}

	f2Vec2 offset(-m_bounding.xCenter(), -m_bounding.yCenter());
	for (size_t i = 0, n = m_sprites.size(); i < n; ++i)
		m_sprites[i]->translate(offset);
	m_bounding.translate(offset);
}	

void CombinationSymbol::initBounding()
{
	for (size_t i = 0, n = m_sprites.size(); i < n; ++i)
	{
		std::vector<f2Vec2> vertices;
		m_sprites[i]->getBounding()->getBoundPos(vertices);
		for (size_t j = 0, m = vertices.size(); j < m; ++j)
			m_bounding.combine(vertices[j]);
	}
}