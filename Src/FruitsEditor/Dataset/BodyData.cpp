#include "BodyData.h"
#include "ChainShape.h"
#include "../File/FileNameParser.h"
#include "../File/LoopsFileAdapter.h"
#include "../File/ChainsFileAdapter.h"
#include "../File/CircleFileAdapter.h"

using namespace FEDITOR;

BodyData::BodyData()
{
}

BodyData::~BodyData()
{
	clear();
}

void BodyData::clear()
{
	for_each(m_fixtures.begin(), m_fixtures.end(), DeletePointerFunctor<FixtureData>());
	m_fixtures.clear();
}

bool BodyData::loadFromFile(const std::string& filename)
{
	clear();

	m_filename = filename;

	FileNameParser::Type type = FileNameParser::getFileType(filename);
	switch (type)
	{
	case FileNameParser::e_loops:
		loadFromLoopsFile(filename);
		break;
	case FileNameParser::e_chains:
		loadFromChainsFile(filename);
		break;
	case FileNameParser::e_circle:
		loadFromCircleFile(filename);
		break;
	default:
		return false;
	}

	return true;
}

void BodyData::loadFromLoopsFile(const std::string& filename)
{
	m_type = e_polygon;

	LoopsFileAdapter fa;
	fa.load(filename);

	m_fixtures.reserve(fa.m_loops.size());
	for (size_t i = 0, n = fa.m_loops.size(); i < n; ++i)
	{
		FixtureData* fd = new FixtureData;
		fd->vertices = fa.m_loops[i]->m_vertices;
		m_fixtures.push_back(fd);
	}
}

void BodyData::loadFromChainsFile(const std::string& filename)
{
	m_type = e_chain;

	ChainsFileAdapter fa;
	fa.load(filename);

	m_fixtures.reserve(fa.m_chains.size());
	for (size_t i = 0, n = fa.m_chains.size(); i < n; ++i)
	{
		FixtureData* fd = new FixtureData;
		fd->vertices = fa.m_chains[i]->m_vertices;
		m_fixtures.push_back(fd);
	}
}

void BodyData::loadFromCircleFile(const std::string& filename)
{
	m_type = e_circle;

	CircleFileAdapter fa;
	fa.load(filename);

	FixtureData* fd = new FixtureData;
	fd->vertices.push_back(f2Vec2(fa.m_width, fa.m_height));
	m_fixtures.push_back(fd);
}