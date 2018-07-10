#include "TEFileAdapter.h"

using namespace deditor::motox;

TEFileAdapter::~TEFileAdapter()
{
	m_data.clear();
}

void TEFileAdapter::resolve(const wxString& filepath)
{
	m_data.clear();

	std::ifstream fin(filepath.fn_str());

	size_t size;
	fin >> size;
	m_data.reserve(size);
	for (size_t i = 0; i < size; ++i)
	{
		Entry entry;

		entry.filepath = StringTools::getLine(fin);

		std::string strLine = StringTools::getLine(fin);
		std::stringstream ss(strLine);

		f2Vec2 pos;
		float angle;
		float scale;
		ss >> entry.pos >> entry.angle >> entry.scale;

		m_data.push_back(entry);
	}

	fin.close();
}