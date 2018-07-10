#include "LibraryImageItem.h"
#include "FileIO.h"

using namespace deditor::boundary_extraction;

LibraryImageItem::LibraryImageItem(const wxString& filename)
{
	loadFromFile(filename);
}

LibraryImageItem::~LibraryImageItem()
{
	delete m_symbol;
}

void LibraryImageItem::loadFromTextFile(std::ifstream& fin)
{
}

void LibraryImageItem::storeToTextFile(std::ofstream& fout) const
{
}

void LibraryImageItem::reloadTexture() const
{
	m_symbol->reloadTexture();
}

void LibraryImageItem::draw() const
{
	m_symbol->draw();
}

void LibraryImageItem::loadResources()
{
	m_symbol = wxgui::SymbolMgr::Instance()->getSymbol(m_filepath);

	m_name = m_symbol->getName();
	m_bitmap = const_cast<wxgui::Bitmap*>(m_symbol->getBitmap());

	FileIO::loadItemShapes(this);
}