#include "FileIO.h"
#include "StagePanel.h"

#include "Tools/ManualComposeFileAdapter.h"

#include <json/json.h>

#ifdef JUNYONG_FORMAT
	#include "Frame/defs.h"
#endif

using namespace deditor::manual_compose;

void FileIO::load(const deditor::ManualComposeFileAdapter& fileAdapter, StagePanel* stage, 
				  wxgui::LibraryPanel* libraryPanel)
{
	wxgui::SymbolMgr::Instance()->clear();
	wxgui::BitmapMgr::Instance()->clear();

#ifdef JUNYONG_FORMAT
	int width = SCREEN_WIDTH,
		height = SCREEN_HEIGHT;
#endif
	if (!fileAdapter.m_bgFilename.IsEmpty())
	{
		stage->setBackground(fileAdapter.m_bgFilename);
#ifdef JUNYONG_FORMAT
		const wxgui::ISymbol& symbol = stage->getBackground()->getSymbol();
		width = symbol.getWidth();
		height = symbol.getHeight();
#endif
	}

	for (size_t i = 0, n = fileAdapter.m_items.size(); i < n; ++i)
	{
		const ManualComposeFileAdapter::Item& item = fileAdapter.m_items[i];
		wxgui::ISymbol* symbol = wxgui::SymbolMgr::Instance()->getSymbol(item.filename);

#ifdef JUNYONG_FORMAT
		f2Vec2 posFixed = item.pos;
		posFixed.x += symbol->getWidth() * 0.5f;
		posFixed.y += symbol->getHeight() * 0.5f;
		posFixed += - f2Vec2(width * 0.5f, height * 0.5f);
		wxgui::ISprite* sprite = wxgui::SpriteFactory::create(symbol);
		sprite->translate(posFixed);
#else
		wxgui::ISprite* sprite = wxgui::SpriteFactory::create(symbol);
		sprite->translate(item.pos);
#endif

		sprite->rotate(item.angle);
		stage->insertSprite(sprite);
	}

	libraryPanel->loadFromSymbolMgr(*wxgui::SymbolMgr::Instance());
}

void FileIO::store(std::ofstream& fout, StagePanel* stage)
{
	if (stage->getBackground())
		fout << stage->getBackground()->getSymbol().getFilepath() << '\n';
	else
		fout << '\n';
#ifdef JUNYONG_FORMAT
	if (stage->getBackground())
	{
		const wxgui::ISymbol& symbol = stage->getBackground()->getSymbol();
		stage->traverseSprites(StoreSpriteVisitor(fout, symbol.getWidth(), symbol.getHeight()));
	}
	else
	{
		stage->traverseSprites(StoreSpriteVisitor(fout, SCREEN_WIDTH, SCREEN_HEIGHT));
	}
#else
	stage->traverseSprites(StoreSpriteVisitor(fout));
#endif

	//////////////////////////////////////////////////////////////////////////

	//Json::Value value;

	//if (stage->getBackground())
	//	value["background"] = stage->getBackground()->getSymbol().getFilepath().ToStdString();
	//else
	//	value["background"] = "NULL";

	//std::vector<wxgui::ISprite*> sprites;
	//stage->traverseSprites(FetchAllVisitor<wxgui::ISprite>(sprites));
	//value["sprite count"] = sprites.size();
	//for (size_t i = 0, n = sprites.size(); i < n; ++i)
	//{
	//	Json::Value spriteValue;
	//	spriteValue["filepath"] = sprites[i]->getSymbol().getFilepath().ToStdString();
	//	value["sprite"][i] = spriteValue;
	//}

	//Json::StyledStreamWriter writer;
	//writer.write(fout, value);
}

//////////////////////////////////////////////////////////////////////////
// class FileIO::StoreSpriteVisitor
//////////////////////////////////////////////////////////////////////////

#ifdef JUNYONG_FORMAT
FileIO::StoreSpriteVisitor::StoreSpriteVisitor(std::ofstream& fout, int width, int height)
	: m_fout(fout)
{
	m_width = width;
	m_height = height;
}
#endif

FileIO::StoreSpriteVisitor::StoreSpriteVisitor(std::ofstream& fout)
	: m_fout(fout)
{
}

FileIO::StoreSpriteVisitor::~StoreSpriteVisitor()
{
	m_fout << m_data.size() << '\n';
	for (size_t i = 0, n = m_data.size(); i < n; ++i)
	{
		wxgui::ISprite* sprite = m_data[i];

#ifdef JUNYONG_FORMAT
		const wxgui::ISymbol& symbol = sprite->getSymbol();
		f2Vec2 posFixed = sprite->getPosition();
		posFixed.x -= symbol.getWidth() * 0.5f;
		posFixed.y -= symbol.getHeight() * 0.5f;
		posFixed += f2Vec2(m_width * 0.5f, m_height * 0.5f);
		m_fout << sprite->getSymbol().getFilepath() << '\n'
			<< posFixed << " " << sprite->getAngle() << " " << symbol.getWidth() << " " << symbol.getHeight() << '\n';
#else
		m_fout << sprite->getSymbol().getFilepath() << '\n'
			<< sprite->getPosition() << " " << sprite->getAngle() << '\n';
#endif
	}
}

void FileIO::StoreSpriteVisitor::visit(IObject* object, bool& bFetchNext)
{
	wxgui::ISprite* sprite = static_cast<wxgui::ISprite*>(object);
	m_data.push_back(sprite);

	bFetchNext = true;
}