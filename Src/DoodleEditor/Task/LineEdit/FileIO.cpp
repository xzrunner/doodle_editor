#include "FileIO.h"
#include "StagePanel.h"

using namespace deditor::line_edit;

void FileIO::load(std::ifstream& fin, StagePanel* stage)
{
	wxgui::SymbolMgr::Instance()->clear();
	wxgui::BitmapMgr::Instance()->clear();

	size_t size;
	fin >> size;
	for (size_t i = 0; i < size; ++i)
	{
		wxgui::ChainShape* chain = new wxgui::ChainShape;
		chain->loadFromTextFile(fin);
		stage->insertShape(chain);
	}
}

void FileIO::store(std::ofstream& fout, StagePanel* stage)
{
	stage->traverseShapes(StoreChainVisitor(fout));
}


//////////////////////////////////////////////////////////////////////////
// class FileIO::StoreChainVisitor
//////////////////////////////////////////////////////////////////////////

FileIO::StoreChainVisitor::StoreChainVisitor(std::ofstream& fout)
	: m_fout(fout)
{
}

FileIO::StoreChainVisitor::~StoreChainVisitor()
{
	m_fout << m_data.size() << '\n';
	for (size_t i = 0, n = m_data.size(); i < n; ++i)
	{
		wxgui::ChainShape* chain = m_data[i];

		const std::vector<f2Vec2>& vertices = chain->getVertices();
		m_fout << vertices.size() << '\n';
		for (size_t i = 0, n = vertices.size(); i < n; ++i)
		{
			f2Vec2 fixed = vertices[i];
			fixed.toInteger();
			m_fout << fixed << " ";
		}
		m_fout << '\n';
		m_fout << chain->isClosed();
		m_fout << '\n';
	}
}

void FileIO::StoreChainVisitor::visit(IObject* object, bool& bFetchNext)
{
	wxgui::ChainShape* chain = static_cast<wxgui::ChainShape*>(object);
	m_data.push_back(chain);

	bFetchNext = true;
}