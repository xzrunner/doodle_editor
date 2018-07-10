#include "FixtureData.h"
#include "Shape.h"
#include "BodyData.h"

using namespace deditor::modeling;

FixtureData::FixtureData()
	: body(NULL)
	, shape(NULL)
	, density(1.0f)
	, friction(0.2f)
	, restitution(0.0f)
	, isSensor(false)
	, categoryBits(0x0001)
	, maskBits(0xFFFF)
	, groupIndex(0)
{
	static int count = 0;
	name = wxT("fixture") + wxString::FromDouble(count++);
}

FixtureData::~FixtureData()
{
	delete shape;
}

bool FixtureData::isContain(const f2Vec2& pos) const
{
	assert(shape);
	return shape->isContain(pos, body->m_sprite->getPosition(), 
		body->m_sprite->getAngle());
}

bool FixtureData::isIntersect(const f2AABB& aabb) const
{
	assert(shape);
	return shape->isIntersect(aabb, body->m_sprite->getPosition(), 
		body->m_sprite->getAngle());
}

void FixtureData::draw(const f2Colorf& cFace, const f2Colorf& cEdge) const
{
	assert(shape);
	shape->draw(cFace, cEdge);
}