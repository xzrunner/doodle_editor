#include "StagePanel.h"
#include "StageCanvas.h"
#include "ToolbarPanel.h"
#include "CompressPicture.h"

using namespace deditor::compress_pictures;

const wxString StagePanel::TMP_FILE = wxT("tmp");

StagePanel::StagePanel(wxWindow* parent)
	: EditPanel(parent)
{
	m_editOP = new wxgui::ZoomViewOP(this, true);
	m_canvas = new StageCanvas(this);
	m_symbol = m_compressedSymbol = NULL;
}

void StagePanel::setToolbar(ToolbarPanel* toolbar) 
{
	m_toolbar = toolbar;
}

void StagePanel::changeSymbol(wxgui::ISymbol* symbol)
{
	if (m_symbol != symbol)
	{
		m_symbol = symbol;
		compressSymbol();
	}
}

void StagePanel::compressSymbol()
{
	if (!m_symbol) return;

	CompressParams params;
	m_toolbar->getCompressParams(params);
	CompressPicture compress(params, m_symbol->getFilepath(), TMP_FILE);
	compress.compress();

	m_compressedSymbol = new wxgui::ImageSymbol;
	m_compressedSymbol->loadFromFile(TMP_FILE);
	m_toolbar->updateParamsPanel(m_symbol->getFilepath(), TMP_FILE);

	Refresh();
}