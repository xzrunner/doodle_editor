#include "ChainShape.h"

#include "Render/PrimitiveDraw.h"
#include "Tools/Settings.h"

using namespace wxgui;

ChainShape::ChainShape()
{
	m_isLoop = false;
}

ChainShape::ChainShape(const ChainShape& chain)
{
	copy(chain.m_vertices.begin(), chain.m_vertices.end(), back_inserter(m_vertices));
	m_isLoop = chain.m_isLoop;
	m_bounding = chain.m_bounding;
}

ChainShape::ChainShape(const std::vector<f2Vec2>& vertices, bool isLoop)
	: m_vertices(vertices)
{
	m_isLoop = isLoop;
	initBounding();
}

ChainShape* ChainShape::clone()
{
	return new ChainShape(*this);
}

void ChainShape::loadFromTextFile(std::ifstream& fin)
{
	m_vertices.clear();
	size_t size;
	fin >> size;
	m_vertices.reserve(size);
	for (size_t i = 0; i < size; ++i)
	{
		f2Vec2 pos;
		fin >> pos;
		m_vertices.push_back(pos);
	}

	fin >> m_isLoop;

// 	int isLoop;
// 	fin >> isLoop;
// 	m_isLoop = (isLoop == 1 ? true : false);

	initBounding();
}

void ChainShape::storeToTextFile(std::ofstream& fout) const
{
	std::vector<f2Vec2> fixed;
	for (size_t i = 0, n = m_vertices.size(); i < n; ++i)
	{
		if (fixed.empty() || f2Math::getDistance(m_vertices[i], fixed.back()) > EPSILON)
			fixed.push_back(m_vertices[i]);
	}

	fout << fixed.size() << '\n';
	for (size_t i = 0, n = fixed.size(); i < n; ++i)
		fout << fixed[i] << " ";
	fout << '\n';
	fout << m_isLoop;
	fout << '\n';
}

bool ChainShape::isContain(const f2Vec2& pos)
{
	if (m_vertices.empty() || !f2Math::isPointInAABB(pos, m_bounding))
		return false;

	size_t index;
	float dis = f2Math::getDisPointToMultiPos(pos, m_vertices, &index);
	if (dis < QUERY_ACCURACY) return true;

	if (m_vertices.size() < 2) return false;
	for (size_t i = 0, n = m_vertices.size() - 1; i < n; ++i)
	{
		float dis = f2Math::getDisPointToSegment(pos, m_vertices[i], m_vertices[i + 1]);
		if (dis < QUERY_ACCURACY) 
			return true;
	}

	return false;
}

bool ChainShape::isIntersect(const f2AABB& aabb)
{
	if (m_vertices.empty() || !f2Math::isAABBIntersectAABB(aabb, m_bounding))	
		return false;

	for (size_t i = 0, n = m_vertices.size(); i < n; ++i)
	{
		if (f2Math::isPointInAABB(m_vertices[i], aabb))
			return true;
	}

	if (m_vertices.size() < 2) return false;
	for (size_t i = 0, n = m_vertices.size() - 1; i < n; ++i)
	{
		if (f2Math::isSegmentIntersectAABB(m_vertices[i], m_vertices[i + 1], aabb))
			return true;
	}

	if (m_isLoop && f2Math::isSegmentIntersectAABB(m_vertices.front(), m_vertices.back(), aabb))
		return true;

	return false;
}

void ChainShape::draw(const f2Colorf& color/* = f2Colorf(0, 0, 0)*/) const
{
	if (m_vertices.empty()) return;

	PrimitiveDraw::resetColorAndTexture();

	PrimitiveDraw::drawPolyline(m_vertices, color, m_isLoop);
	if (Settings::ctlPosSize != 0)
		PrimitiveDraw::drawCircles(m_vertices, Settings::ctlPosSize, f2Colorf(0.4f, 0.8f, 0.4f));
}

void ChainShape::insertVertices(size_t index, const f2Vec2& pos)
{
	if (index <= m_vertices.size())
		m_vertices.insert(m_vertices.begin() + index, pos);
}

void ChainShape::removeVertices(const f2Vec2& pos)
{
	std::vector<f2Vec2>::iterator itr = m_vertices.begin();
	for ( ; itr != m_vertices.end(); ++itr)
	{
		if (*itr == pos)
		{
			m_vertices.erase(itr);
			break;
		}
	}
}

void ChainShape::changeVertices(const f2Vec2& from, const f2Vec2& to)
{
	size_t index = 0;
	for (size_t n = m_vertices.size(); index < n; ++index)
	{
		if (m_vertices[index] == from)
			break;
	}

	if (index == m_vertices.size()) return;

	m_vertices[index] = to;
	if (from.x == m_bounding.xMin || from.x == m_bounding.xMax
		|| from.y == m_bounding.yMin || from.y == m_bounding.yMax)
		initBounding();
	else 
		m_bounding.combine(to);
}

void ChainShape::setVertices(const std::vector<f2Vec2>& vertices)
{
	m_vertices = vertices;
	initBounding();
}

void ChainShape::initBounding()
{
	m_bounding.makeInfinite();
	for (size_t i = 0, n = m_vertices.size(); i < n; ++i)
		m_bounding.combine(m_vertices[i]);
}