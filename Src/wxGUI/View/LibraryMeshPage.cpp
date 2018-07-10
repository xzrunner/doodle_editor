#include "LibraryMeshPage.h"
#include "LibraryList.h"

#include "Dataset/SymbolMgr.h"
#include "Dataset/MeshSymbol.h"
#include "Tools/FileNameParser.h"

using namespace wxgui;

LibraryMeshPage::LibraryMeshPage(wxWindow* parent)
	: ILibraryPage(parent, wxT("网格"))
{
	initLayout();
}

bool LibraryMeshPage::isHandleSymbol(ISymbol* symbol) const
{
	return dynamic_cast<MeshSymbol*>(symbol) != NULL;
}

void LibraryMeshPage::onAddPress(wxCommandEvent& event)
{
	wxString filter = "*_" + FileNameParser::getFileTag(FileNameParser::e_mesh) + ".txt";
	wxFileDialog dlg(this, wxT("选择mesh文件"), wxEmptyString, 
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
