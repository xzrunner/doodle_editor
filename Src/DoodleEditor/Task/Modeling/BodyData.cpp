#include "BodyData.h"
#include "FixtureData.h"

using namespace deditor::modeling;

BodyData::BodyData()
	: m_type(e_static)
	, m_gravityScale(1.0f)
	, m_sprite(NULL)
{
	static int count = 0;
	m_name = wxT("body") + wxString::FromDouble(count++);
}

BodyData::~BodyData()
{
	for_each(m_fixtures.begin(), m_fixtures.end(), DeletePointerFunctor<FixtureData>());
	m_fixtures.clear();
}

bool BodyData::isContain(const f2Vec2& pos) const
{
	for (size_t i = 0, n = m_fixtures.size(); i < n; ++i)
		if (m_fixtures[i]->isContain(pos))
			return true;
	return false;
}

bool BodyData::isIntersect(const f2AABB& aabb) const
{
	for (size_t i = 0, n = m_fixtures.size(); i < n; ++i)
		if (m_fixtures[i]->isIntersect(aabb))
			return true;
	return false;
}

void BodyData::draw(const f2Colorf& cFace, const f2Colorf& cEdge) const
{
	for (size_t i = 0, n = m_fixtures.size(); i < n; ++i)
		m_fixtures[i]->draw(cFace, cEdge);
}