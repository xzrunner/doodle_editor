#include "BodyFactory.h"
#include "PolygonBody.h"
#include "ChainBody.h"
#include "CircleBody.h"
#include "BodyData.h"
#include "ChainShape.h"

using namespace FEDITOR;

b2World* BodyFactory::m_world = NULL;

Body* BodyFactory::createBody(const std::string& filename, float scale/* = 1.0f*/)
{
	Body* body = NULL;
	BodyData* bd = BodyDataMgr::Instance()->getItem(filename);
	switch (bd->type())
	{
	case BodyData::e_polygon:
		body = new PolygonBody(m_world, *bd, scale);
		break;
	case BodyData::e_chain:
		body = new ChainBody(m_world, *bd, scale);
		break;
	case BodyData::e_circle:
		body = new CircleBody(m_world, *bd, scale);
		break;
	}
	return body;
}