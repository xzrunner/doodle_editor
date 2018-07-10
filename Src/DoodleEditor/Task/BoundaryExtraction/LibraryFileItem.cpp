#include "LibraryFileItem.h"
#include "FileIO.h"

#include "Tools/ManualComposeFileAdapter.h"

using namespace deditor::boundary_extraction;

LibraryFileItem::LibraryFileItem(const wxString& filename)
{
	loadFromFile(filename);
}

LibraryFileItem::~LibraryFileItem()
{
	clear();
}

void LibraryFileItem::loadFromTextFile(std::ifstream& fin)
{
}

void LibraryFileItem::storeToTextFile(std::ofstream& fout) const
{
}

void LibraryFileItem::reloadTexture() const
{

}

void LibraryFileItem::loadResources()
{
	FileIO::loadItemShapes(this);

	clear();

	ManualComposeFileAdapter fileAdapter;
	fileAdapter.load(m_filepath.c_str());

	m_sprites.reserve(fileAdapter.m_items.size());
	for (size_t i = 0, n = fileAdapter.m_items.size(); i < n; ++i)
	{
		const ManualComposeFileAdapter::Item& item = fileAdapter.m_items[i];
		wxgui::ISymbol* symbol = wxgui::SymbolMgr::Instance()->getSymbol(item.filename);
		wxgui::ISprite* sprite = wxgui::SpriteFactory::create(symbol);
		sprite->translate(item.pos);
		m_sprites.push_back(sprite);
	}
}

void LibraryFileItem::draw() const
{
	for (size_t i = 0, n = m_sprites.size(); i < n; ++i)
		wxgui::SpriteDraw::drawSprite(m_sprites[i]);
}

void LibraryFileItem::clear()
{
	for_each(m_sprites.begin(), m_sprites.end(), DeletePointerFunctor<wxgui::ISprite>());
	m_sprites.clear();
}
