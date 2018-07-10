#include "FileIO.h"
#include "StagePanel.h"
#include "ToolbarPanel.h"
#include "Blackboard.h"

using namespace deditor::monster;


void FileIO::load(std::ifstream& fin, StagePanel* stage, 
				  wxgui::LibraryPanel* libraryPanel,
				  ToolbarPanel* toolbar)
{
	wxgui::SymbolMgr::Instance()->clear();
	wxgui::BitmapMgr::Instance()->clear();

	int time, length/*, edge*/, min, max;
	fin >> time >> length/* >> edge*/ >> min >> max;
	toolbar->setValues(time, length/*, edge*/, min, max);
	
	size_t size;
	fin >> size;
	for (size_t i = 0; i < size; ++i)
	{
		std::string filepath;
//		f2Vec2 pos;
		float v0, v1;
		float id;
		
		filepath = StringTools::getLine(fin);
//		fin >> pos >> id;
		fin >> v0 >> v1 >> id;

		wxgui::ISymbol* symbol = wxgui::SymbolMgr::Instance()->getSymbol(filepath);
// 		//////////////////////////////////////////////////////////////////////////
// 		const float factor = (Blackboard::edge * Blackboard::col) / 480.0f;
// 		pos *= factor;
// 		wxgui::ISprite* sprite = new wxgui::ImageSprite(symbol, pos);
		//////////////////////////////////////////////////////////////////////////
		f2Vec2 pos;
		pos.x = (v0 - 1 + 0.5f) * Blackboard::edge;
		if (v1 < 0)
			pos.y = (v1 + 1 - 0.5f) * Blackboard::edge;
		else
			pos.y = Blackboard::edge * Blackboard::length * v1;
		wxgui::ISprite* sprite = wxgui::SpriteFactory::create(symbol);
		sprite->translate(pos);
		//////////////////////////////////////////////////////////////////////////
		
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
		<< Blackboard::length << '\n'
		<< Blackboard::min << '\n'
		<< Blackboard::max << '\n';

	m_fout << m_data.size() << '\n';
	for (size_t i = 0, n = m_data.size(); i < n; ++i)
	{
		wxgui::ISprite* sprite = m_data[i];

		m_fout << sprite->getSymbol().getFilepath() << '\n';

		float* data = static_cast<float*>(sprite->getUserData());

		//////////////////////////////////////////////////////////////////////////
		// 	const float factor = 480.0f / (Blackboard::edge * Blackboard::col);
		// 	m_fout << sprite->getPosition() * factor << " " << data[0] << '\n';

		//////////////////////////////////////////////////////////////////////////

		float v0, v1;
		const f2Vec2& pos = sprite->getPosition();
		if (pos.y < 0)
		{
			const int col = (int) (pos.x / Blackboard::edge),
				row = (int) (-pos.y / Blackboard::edge);
			v0 = col + 1;
			v1 = - (row + 1);
		}
		else
		{
			const int col = (int) (pos.x / Blackboard::edge);
			v0 = col + 1;
			v1 = pos.y / (Blackboard::edge * Blackboard::length);
		}
		m_fout << v0 << " " << v1 << " " << data[0] << '\n';

		//////////////////////////////////////////////////////////////////////////
	}
}

void FileIO::StoreSpriteVisitor::
visit(IObject* object, bool& bFetchNext)
{
	wxgui::ISprite* sprite = static_cast<wxgui::ISprite*>(object);
	m_data.push_back(sprite);

	bFetchNext = true;
}
