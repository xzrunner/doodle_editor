#include "FileIO.h"
#include "StagePanel.h"

using namespace deditor::skater;

void FileIO::load(std::ifstream& fin, StagePanel* stage, 
				  wxgui::LibraryPanel* libraryPanel)
{
	//	loadOld(fin, stage, libraryPanel);
	loadNew(fin, stage, libraryPanel);
}

void FileIO::store(std::ofstream& fout, StagePanel* stage)
{
	fout << "1" << '\n';
	stage->traverseSprites(StoreSpriteVisitor(fout));
	stage->traverseShapes(StoreChainVisitor(fout));
}

void FileIO::loadOld(std::ifstream& fin, StagePanel* stage, 
					 wxgui::LibraryPanel* libraryPanel)
{
	wxgui::SymbolMgr::Instance()->clear();
	wxgui::BitmapMgr::Instance()->clear();

	size_t layerSize;
	fin >> layerSize;
	for (size_t i = 0; i < layerSize; ++i)
	{
		size_t spriteSize;
		fin >> spriteSize;
		for (size_t j = 0; j < spriteSize; ++j)
		{
			std::string strLine = StringTools::getLine(fin);
			std::stringstream ss(strLine);

			std::string filename;
			f2Vec2 pos;
			float angle;
			float xScale, yScale;
			float* data = new float[4];

			ss >> filename >> pos >> angle
				>> xScale >> yScale
				>> data[0] >> data[1] >> data[2] >> data[3];

			wxgui::ISymbol* symbol = wxgui::SymbolMgr::Instance()->getSymbol(filename);
			wxgui::ISprite* sprite = wxgui::SpriteFactory::create(symbol);
			sprite->setTransform(pos, angle);
			sprite->setUserData(data);
			stage->insertSprite(sprite);
			sprite->release();
		}
	}

	libraryPanel->loadFromSymbolMgr(*wxgui::SymbolMgr::Instance());
}

void FileIO::loadNew(std::ifstream& fin, StagePanel* stage, 
					 wxgui::LibraryPanel* libraryPanel)
{
	loadSprites(fin, stage, libraryPanel);
	loadChains(fin, stage);
}

void FileIO::loadSprites(std::ifstream& fin, StagePanel* stage, 
						 wxgui::LibraryPanel* libraryPanel)
{
	wxgui::SymbolMgr::Instance()->clear();
	wxgui::BitmapMgr::Instance()->clear();

	size_t layerSize;
	fin >> layerSize;
	for (size_t i = 0; i < layerSize; ++i)
	{
		size_t spriteSize;
		fin >> spriteSize;
		for (size_t j = 0; j < spriteSize; ++j)
		{
			std::string filename = StringTools::getLine(fin);

			std::string strLine = StringTools::getLine(fin);
			std::stringstream ss(strLine);

			f2Vec2 pos;
			float angle;
			float xScale, yScale;
			float* data = new float[4];

			ss  >> pos >> angle
				>> xScale >> yScale
				>> data[0] >> data[1] >> data[2] >> data[3];

			wxgui::ISymbol* symbol = wxgui::SymbolMgr::Instance()->getSymbol(filename);
			wxgui::ISprite* sprite = wxgui::SpriteFactory::create(symbol);
			sprite->setTransform(pos, angle);
			sprite->setUserData(data);
			stage->insertSprite(sprite);
			sprite->release();
		}
	}

	libraryPanel->loadFromSymbolMgr(*wxgui::SymbolMgr::Instance());
}

void FileIO::loadChains(std::ifstream& fin, StagePanel* stage)
{
 	size_t size;
 	fin >> size;
 	for (size_t i = 0; i < size; ++i)
 	{
 		wxgui::ChainShape* chain = new wxgui::ChainShape;
 		chain->loadFromTextFile(fin);
		int* data = new int[1];
		fin >> data[0];
		chain->setUserData(data);
		stage->insertShape(chain);
 	} 
}

//////////////////////////////////////////////////////////////////////////
// class FileIO::StoreSpriteVisitor
//////////////////////////////////////////////////////////////////////////

FileIO::StoreSpriteVisitor::StoreSpriteVisitor(std::ofstream& fout)
	: m_fout(fout)
{
}

FileIO::StoreSpriteVisitor::~StoreSpriteVisitor()
{
	m_fout << m_data.size() << '\n';
	for (size_t i = 0, n = m_data.size(); i < n; ++i)
	{
		wxgui::ISprite* sprite  = m_data[i];

		m_fout << sprite->getSymbol().getFilepath() << '\n';
		m_fout << sprite->getPosition() << " " << sprite->getAngle() << " 1 1";
		float* data = static_cast<float*>(sprite->getUserData());
		for (size_t i = 0; i < 4; ++i)
			m_fout << " " << data[i];
		m_fout << '\n';
	}
}

void FileIO::StoreSpriteVisitor::visit(IObject* object, bool& bFetchNext)
{
	wxgui::ISprite* sprite = static_cast<wxgui::ISprite*>(object);
	m_data.push_back(sprite);

	bFetchNext = true;
}

//////////////////////////////////////////////////////////////////////////
// class FileIO::StoreChainVisitor
//////////////////////////////////////////////////////////////////////////

FileIO::StoreChainVisitor::StoreChainVisitor(std::ofstream& fout)
	: m_fout(fout)
{
}

FileIO::StoreChainVisitor::~StoreChainVisitor()
{
	m_fout << m_data.size() << '\n';
	for (size_t i = 0, n = m_data.size(); i < n; ++i)
	{
		wxgui::ChainShape* chain = m_data[i];
		chain->storeToTextFile(m_fout);
		int* data = static_cast<int*>(chain->getUserData());
		m_fout << data[0] << '\n';
	}
}

void FileIO::StoreChainVisitor::visit(IObject* object, bool& bFetchNext)
{
	wxgui::ChainShape* chain = static_cast<wxgui::ChainShape*>(object);
	m_data.push_back(chain);

	bFetchNext = true;
}