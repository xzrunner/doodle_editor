#include "LibraryBreakableItem.h"

using namespace deditor::motox;

const wxString LibraryBreakableItem::TAG = wxT("breakable");

LibraryBreakableItem::LibraryBreakableItem()
	: m_spriteCombine(NULL)
	, m_meshCombine(NULL)
{
}

void LibraryBreakableItem::loadFromTextFile(std::ifstream& fin)
{

}

void LibraryBreakableItem::storeToTextFile(std::ofstream& fout) const
{

}

void LibraryBreakableItem::reloadTexture() const
{

}

void LibraryBreakableItem::draw() const
{
	if (m_spriteCombine) 
		m_spriteCombine->draw();
	else 
		m_meshCombine->draw();
}

float LibraryBreakableItem::getWidth() const
{
	return 0;
}

float LibraryBreakableItem::getHeight() const
{
	return 0;
}

void LibraryBreakableItem::loadResources()
{
	std::ifstream fin(m_filepath.fn_str());
	wxString spritesPath = StringTools::getLine(fin);
	wxString meshesPath = StringTools::getLine(fin);
	fin.close();

	if (spritesPath != wxT("NULL"))
	{
		wxgui::ISymbol* symbol = wxgui::SymbolMgr::Instance()->getSymbol(spritesPath);
		m_spriteCombine = dynamic_cast<wxgui::CombinationSymbol*>(symbol);
		assert(m_spriteCombine);
	}

	wxgui::ISymbol* symbol = wxgui::SymbolMgr::Instance()->getSymbol(meshesPath);
	m_meshCombine = dynamic_cast<wxgui::CombinationSymbol*>(symbol);
	assert(m_meshCombine);
}