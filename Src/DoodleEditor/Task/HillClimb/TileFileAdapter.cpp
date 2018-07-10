#include "TileFileAdapter.h"

using namespace deditor::hill_climb;

TileFileAdapter::~TileFileAdapter()
{
	for (size_t i = 0, n = m_sprites.size(); i < n; ++i)
		m_sprites[i]->release();
	m_sprites.clear();
}

void TileFileAdapter::resolve(const wxString& filepath)
{
	std::ifstream fin(filepath.fn_str());

	size_t size;
	fin >> size;
	m_sprites.reserve(size);
	for (size_t i = 0; i < size; ++i)
	{
		std::string filepath = StringTools::getLine(fin);

		std::string strLine = StringTools::getLine(fin);
		std::stringstream ss(strLine);

		f2Vec2 pos;
		ss >> pos;

		wxgui::ISymbol* symbol = wxgui::SymbolMgr::Instance()->getSymbol(filepath);
		wxgui::ISprite* sprite = wxgui::SpriteFactory::create(symbol);
		sprite->translate(pos);
		m_sprites.push_back(sprite);
	}

	fin.close();
}