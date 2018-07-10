#include "LibrarySymbolList.h"
#include "StagePanel.h"
#include "ToolbarPanel.h"
#include "CompressPicture.h"

using namespace deditor::compress_pictures;

LibrarySymbolList::LibrarySymbolList(wxWindow* parent)
	: wxgui::LibraryList(parent)
{
}

void LibrarySymbolList::compressAll(const CompressParams& params, const wxString& ext) const
{
	int index = 0;
	while (true)
	{
		wxgui::ISymbol* symbol = getSymbol(index++);
		if (!symbol) break;

		const wxString& src = symbol->getFilepath();
		wxString dst = src;
		dst.insert(src.find_last_of('.'), ext);

		CompressPicture compress(params, src, dst);
		compress.compress();
	}
}

void LibrarySymbolList::onListSelected(wxCommandEvent& event)
{
	wxgui::ISymbol* symbol = getSymbol(event.GetInt());
	m_stage->changeSymbol(symbol);
	m_toolbar->changeSymbol(symbol);
}

void LibrarySymbolList::registerContext(StagePanel* stage, ToolbarPanel* toolbar)
{
	m_stage = stage;
	m_toolbar = toolbar;
}