#include "FileIO.h"
#include "StagePanel.h"
#include "ToolbarPanel.h"
#include "Blackboard.h"

using namespace deditor::magic_defence;


void FileIO::load(std::ifstream& fin, StagePanel* stage, 
				  wxgui::LibraryPanel* libraryPanel,
				  ToolbarPanel* toolbar)
{
	wxgui::SymbolMgr::Instance()->clear();
	wxgui::BitmapMgr::Instance()->clear();

	int time, length;
	fin >> time >> length;
	toolbar->setValues(time, length);
	
	size_t size;
	fin >> size;
	for (size_t i = 0; i < size; ++i)
	{
		std::string filepath;
		float v0, v1;
		float id;
		
		filepath = StringTools::getLine(fin);
		fin >> v0 >> v1 >> id;

		wxgui::ISymbol* symbol = wxgui::SymbolMgr::Instance()->getSymbol(filepath);

		f2Vec2 pos;
		pos.x = Blackboard::edge * Blackboard::length * v0;
		pos.y = (v1 - 1 + 0.5f) * Blackboard::edge;
		wxgui::ISprite* sprite = wxgui::SpriteFactory::create(symbol);
		sprite->translate(pos);

		float* data = new float[1];
		data[0] = id;
		sprite->setUserData(data);

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
	m_fout << Blackboard::time << '\n'
		<< Blackboard::length << '\n';

	m_fout << m_data.size() << '\n';
	for (size_t i = 0, n = m_data.size(); i < n; ++i)
	{
		wxgui::ISprite* sprite = m_data[i];

		m_fout << sprite->getSymbol().getFilepath() << '\n';

		float v0, v1;
		const f2Vec2& pos = sprite->getPosition();

		const int row = (int) (pos.y / Blackboard::edge);
		v0 = pos.x / (Blackboard::edge * Blackboard::length);
		v1 = row + 1;

		float* data = static_cast<float*>(sprite->getUserData());

		m_fout << v0 << " " << v1 << " " << data[0] << '\n';
	}
}

void FileIO::StoreSpriteVisitor::
visit(IObject* object, bool& bFetchNext)
{
	wxgui::ISprite* sprite = static_cast<wxgui::ISprite*>(object);
	m_data.push_back(sprite);

	bFetchNext = true;
}
