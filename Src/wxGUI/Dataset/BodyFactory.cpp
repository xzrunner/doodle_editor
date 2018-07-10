#include "BodyFactory.h"
#include "BodyData.h"
#include "PolygonBody.h"
#include "CircleBody.h"
#include "ComplexBody.h"

using namespace wxgui;

b2World* BodyFactory::m_world = NULL;

IBody* BodyFactory::createBody(const wxString& filename, float scale/* = 1.0f*/)
{
	IBody* body = NULL;
	BodyData* bd = BodyDataMgr::Instance()->getItem(filename);
	switch (bd->type())
	{
	case BodyData::e_polygon:
		body = new PolygonBody(m_world, *bd, scale);
		break;
	case BodyData::e_circle:
		body = new CircleBody(m_world, *bd, scale);
	}
	return body;
}

// todo: BodyData's destructor func will delete the FixtureData pointer
IBody* BodyFactory::createBody(const std::vector<f2Vec2>& triangles, float scale/* = 1.0f*/)
{
	BodyData bd;

	size_t index = 0;
	for (size_t i = 0, n = triangles.size() / 3; i < n; ++i)
	{
		BodyData::FixtureData* fd = new BodyData::FixtureData;
		fd->vertices.push_back(triangles[index++]);
		fd->vertices.push_back(triangles[index++]);
		fd->vertices.push_back(triangles[index++]);
		bd.insertFixture(fd);
	}

	return new PolygonBody(m_world, bd, scale);
}

IBody* BodyFactory::createBody(const std::vector<FixtureDataInfo>& fixtures, float scale /*= 1.0f*/)
{
	return new ComplexBody(m_world, fixtures, scale);
}