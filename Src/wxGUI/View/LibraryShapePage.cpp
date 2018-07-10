#include "LibraryShapePage.h"
#include "LibraryList.h"

#include "Dataset/SymbolMgr.h"
#include "Dataset/ISymbol.h"
#include "Dataset/ShapeSymbol.h"
#include "Tools/FileNameParser.h"

using namespace wxgui;

LibraryShapePage::LibraryShapePage(wxWindow* parent)
	: ILibraryPage(parent, wxT("ͼ��"))
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
	wxFileDialog dlg(this, wxT("ѡ��ͼ���ļ�"), wxEmptyString, 
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
