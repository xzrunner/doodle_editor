#include "BodyData.h"
#include "ChainShape.h"
#include "Tools/FileNameParser.h"
#include "Tools/PolylineFileAdapter.h"
#include "Tools/CircleFileAdapter.h"

using namespace wxgui;

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

bool BodyData::loadFromFile(const wxString& filename)
{
	clear();

	m_filename = filename;

	FileNameParser::Type type = FileNameParser::getFileType(filename);
	switch (type)
	{
	case FileNameParser::e_mesh:
		loadFromMeshFile(filename);
		break;
	case FileNameParser::e_polyline:
		loadFromPolygonFile(filename);
		break;
	case FileNameParser::e_circle:
		loadFromCircleFile(filename);
		break;
	default:
		return false;
	}

	return true;
}

void BodyData::loadFromMeshFile(const wxString& filename)
{
	m_type = e_mesh;

	MeshSymbol symbol;
	symbol.loadFromFile(filename);

	const std::vector<f2Vec2>& triangles = symbol.getVertices();

	size_t size = triangles.size() / 3;
	m_fixtures.reserve(size);
	size_t index = 0;
	for (size_t i = 0; i < size; ++i)
	{
		FixtureData* fd = new FixtureData;
		fd->vertices.push_back(triangles[index++]);
		fd->vertices.push_back(triangles[index++]);
		fd->vertices.push_back(triangles[index++]);
		m_fixtures.push_back(fd);
	}
}

void BodyData::loadFromPolygonFile(const wxString& filename)
{
	m_type = e_polygon;

	std::vector<ChainShape*> chains;
	PolylineFileAdapter fileAdapter(chains);
	fileAdapter.load(filename.c_str());

	m_fixtures.reserve(fileAdapter.m_chains.size());
	for (size_t i = 0, n = fileAdapter.m_chains.size(); i < n; ++i)
	{
		FixtureData* fd = new FixtureData;
		fd->vertices = fileAdapter.m_chains[i]->getVertices();
		m_fixtures.push_back(fd);
	}

	for_each(chains.begin(), chains.end(), DeletePointerFunctor<ChainShape>());
}

void BodyData::loadFromCircleFile(const wxString& filename)
{
	m_type = e_circle;

	CircleFileAdapter fa;
	fa.load(filename);

	FixtureData* fd = new FixtureData;
	fd->vertices.push_back(f2Vec2(fa.m_width, fa.m_height));
	m_fixtures.push_back(fd);
}