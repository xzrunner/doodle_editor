#include "FileIO.h"
#include "LibraryPanel.h"
#include "LibraryItem.h"

using namespace deditor::boundary_extraction;

void FileIO::load(std::ifstream& fin, LibraryPanel* library)
{
	wxgui::SymbolMgr::Instance()->clear();
	wxgui::BitmapMgr::Instance()->clear();
	library->loadFromTextFile(fin);
}

void FileIO::store(std::ofstream& fout, LibraryPanel* library)
{
	library->storeToTextFile(fout);
}

void FileIO::loadItemShapes(LibraryItem* item)
{
	wxString src = item->getFilepath();
	wxString dst = wxgui::FilenameTools::getFilePathExceptExtension(src)
		+ "_" + wxgui::FileNameParser::getFileTag(wxgui::FileNameParser::e_polyline) 
		+ wxT(".txt");
	if (!wxgui::FilenameTools::isExist(dst)) return;

	std::vector<wxgui::ChainShape*>* data = new std::vector<wxgui::ChainShape*>;
	wxgui::PolylineFileAdapter fileAdapter(*data);
	fileAdapter.load(dst.c_str());

	item->setUserData(data);
}

//////////////////////////////////////////////////////////////////////////
// class FileIO::StoreItemVisitor
//////////////////////////////////////////////////////////////////////////

FileIO::StoreItemVisitor::StoreItemVisitor(std::ofstream& fout)
	: m_fout(fout)
{
}

FileIO::StoreItemVisitor::~StoreItemVisitor()
{
	m_fout << m_data.size() << '\n';
	for (size_t i = 0, n = m_data.size(); i < n; ++i)
	{
		LibraryItem* item = m_data[i];
		m_fout << item->getFilepath() << '\n';
		storeChainShapes(item);
	}
}

void FileIO::StoreItemVisitor::visit(IObject* object, bool& bFetchNext)
{
	LibraryItem* item = static_cast<LibraryItem*>(object);
	m_data.push_back(item);

	bFetchNext = true;
}

void FileIO::StoreItemVisitor::storeChainShapes(const LibraryItem* item) const
{
	std::vector<wxgui::ChainShape*>* chains 
		= static_cast<std::vector<wxgui::ChainShape*>*>(item->getUserData());
	if (!chains || chains->empty()) return;

	wxString src = item->getFilepath();
	wxString dst = wxgui::FilenameTools::getFilePathExceptExtension(src)
		+ "_" + wxgui::FileNameParser::getFileTag(wxgui::FileNameParser::e_polyline)
		+ wxT(".txt");

	wxgui::PolylineFileAdapter fileAdapter(*chains);
	fileAdapter.setImgPath(src);
	fileAdapter.store(dst.c_str());
}