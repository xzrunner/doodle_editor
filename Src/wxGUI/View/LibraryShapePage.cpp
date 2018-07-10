#include "LibraryShapePage.h"
#include "LibraryList.h"

#include "Dataset/SymbolMgr.h"
#include "Dataset/ISymbol.h"
#include "Dataset/ShapeSymbol.h"
#include "Tools/FileNameParser.h"

using namespace wxgui;

LibraryShapePage::LibraryShapePage(wxWindow* parent)
	: ILibraryPage(parent, wxT("图形"))
{
	initLayout();
}

bool LibraryShapePage::isHandleSymbol(ISymbol* symbol) const
{
	return dynamic_cast<ShapeSymbol*>(symbol) != NULL;
}

void LibraryShapePage::onAddPress(wxCommandEvent& event)
{
	wxString filter = "*_" + FileNameParser::getFileTag(FileNameParser::e_polygon) + ".txt";
	wxFileDialog dlg(this, wxT("选择图形文件"), wxEmptyString, 
		wxEmptyString, filter, wxFD_OPEN | wxFD_MULTIPLE);
	if (dlg.ShowModal() == wxID_OK)
	{
		wxArrayString filenames;
		dlg.GetPaths(filenames);
		for (size_t i = 0, n = filenames.size(); i < n; ++i)
		{
			ISymbol* symbol = SymbolMgr::Instance()->getSymbol(filenames[i]);
			m_list->insert(symbol);
		}
	}
}
