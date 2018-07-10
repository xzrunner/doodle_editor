#include "FileIO.h"
#include "StagePanel.h"

using namespace deditor::shoot_bubble;

void FileIO::load(std::ifstream& fin, StagePanel* stage, 
				  wxgui::LibraryPanel* libraryPanel)
{
	wxgui::SymbolMgr::Instance()->clear();
	wxgui::BitmapMgr::Instance()->clear();

	size_t size;
	fin >> size;
	for (size_t i = 0; i < size; ++i)
	{
		std::string filepath;
		int row, col;

		filepath = StringTools::getLine(fin);
		fin >> row >> col;

		wxgui::ISymbol* symbol = wxgui::SymbolMgr::Instance()->getSymbol(filepath);
		f2Vec2 pos;
		stage->transGridPosToCoords(row, col, pos);
		wxgui::ISprite* sprite = wxgui::SpriteFactory::create(symbol);
		sprite->translate(pos);
		stage->insertSprite(sprite);
	}

	libraryPanel->loadFromSymbolMgr(*wxgui::SymbolMgr::Instance());
}

void FileIO::store(std::ofstream& fout, StagePanel* stage)
{
	stage->traverseSprites(StoreSpriteVisitor(fout, stage));
}

//////////////////////////////////////////////////////////////////////////
// class FileIO::StoreSpriteVisitor
//////////////////////////////////////////////////////////////////////////

FileIO::StoreSpriteVisitor::
StoreSpriteVisitor(std::ofstream& fout, StagePanel* stage)
	: m_fout(fout)
	, m_stage(stage)
{
}

FileIO::StoreSpriteVisitor::
~StoreSpriteVisitor()
{
	m_fout << m_data.size() << '\n';
	for (size_t i = 0, n = m_data.size(); i < n; ++i)
	{
		wxgui::ISprite* sprite = m_data[i];

		m_fout << sprite->getSymbol().getFilepath() << '\n';

		int row, col;
		m_stage->transCoordsToGridPos(sprite->getPosition(), row, col);
		m_fout << row << " " << col << '\n';
	}
}

void FileIO::StoreSpriteVisitor::
visit(IObject* object, bool& bFetchNext)
{
	wxgui::ISprite* sprite = static_cast<wxgui::ISprite*>(object);
	m_data.push_back(sprite);

	bFetchNext = true;
}
