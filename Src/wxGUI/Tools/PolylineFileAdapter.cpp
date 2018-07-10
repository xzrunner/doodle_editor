#include "PolylineFileAdapter.h"

using namespace wxgui;

PolylineFileAdapter::PolylineFileAdapter(std::vector<ChainShape*>& chains)
	: m_chains(chains)
{
}

void PolylineFileAdapter::load(const char* filename)
{
	std::ifstream fin(filename);

	std::string line;
	getline(fin, line);
	m_imgPath = line;

	size_t size;
	fin >> size;
	for (size_t i = 0; i < size; ++i)
	{
		ChainShape* chain = new ChainShape();
		chain->loadFromTextFile(fin);
		m_chains.push_back(chain);
	}

	fin.close();
}

void PolylineFileAdapter::store(const char* filename)
{
	std::ofstream fout(filename);

	fout << m_imgPath << '\n';
	fout << m_chains.size() << '\n';
	for (size_t i = 0, n = m_chains.size(); i < n; ++i)
		m_chains[i]->storeToTextFile(fout);

	fout.close();
}