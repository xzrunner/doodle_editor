#include "ChainShape.h"

using namespace FEDITOR;

ChainShape::ChainShape()
	: Shape(e_chain)
{
	m_isLoop = false;
}

ChainShape::ChainShape(std::vector<f2Vec2> vertices, bool isLoop)
	: Shape(e_chain)
{
	std::copy(vertices.begin(), vertices.end(), back_inserter(m_vertices));
	m_isLoop = isLoop;
}

ChainShape::ChainShape(const ChainShape& chain)
	: Shape(e_chain)
{
	std::copy(chain.m_vertices.begin(), chain.m_vertices.end(), back_inserter(m_vertices));
	m_isLoop = chain.m_isLoop;
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

// 	int isLoop;
// 	fin >> isLoop;
// 	m_isLoop = (isLoop == 1 ? true : false);

	fin >> m_isLoop;
}

void ChainShape::storeToTextFile(std::ofstream& fout) const
{
	fout << "type " << m_type << '\n';

	fout << m_vertices.size() << '\n';
	for (size_t i = 0, n = m_vertices.size(); i < n; ++i)
	{
		const f2Vec2& pos = m_vertices[i];
		fout << pos << " ";
	}
	fout << '\n';

//	fout << m_isLoop ? 1 : 0;
//	fout << '\n';

	fout << m_isLoop << '\n';
}

bool ChainShape::isContain(const f2Vec2& pos, float scale) const
{
	if (m_isLoop)
		return f2Math::isPointInArea(pos, m_vertices);
	else
	{
		size_t index;
		float dis = f2Math::getDisPointToMultiPos(pos, m_vertices, &index);
		if (dis < QUERY_ACCURACY * scale) return true;

		if (m_vertices.size() < 2) return false;
		for (size_t i = 0, n = m_vertices.size() - 1; i < n; ++i)
		{
			float dis = f2Math::getDisPointToSegment(pos, m_vertices[i], m_vertices[i + 1]);
			if (dis < QUERY_ACCURACY * scale) return true;
		}

		return false;
	}
}

void ChainShape::getAABB(f2AABB& aabb, const f2Vec2& position, float angle) const
{
	aabb.makeInfinite();
	for (size_t i = 0, n = m_vertices.size(); i < n; ++i)
	{
		const f2Vec2& src = m_vertices[i];
		f2Vec2 transform = f2Math::rotateVector(src, angle) + position;
		aabb.combine(transform);
	}
}