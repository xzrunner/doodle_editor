#ifndef _FEDITOR_CHAIN_SHAPE_H_
#define _FEDITOR_CHAIN_SHAPE_H_
#include "Shape.h"

namespace FEDITOR
{
	class ChainShape : public Shape
	{
	public:
		ChainShape();
		ChainShape(std::vector<f2Vec2> vertices, bool isLoop);
		ChainShape(const ChainShape& chain);

		//
		// IObject interface
		//
		virtual ChainShape* clone();

		//
		// ISerializable interface
		//
		virtual void loadFromTextFile(std::ifstream& fin);
		virtual void storeToTextFile(std::ofstream& fout) const;

		//
		// Shape interface
		//
		virtual bool isContain(const f2Vec2& pos, float scale) const;
		virtual void getAABB(f2AABB& aabb, const f2Vec2& position, float angle) const;

		size_t size() const;
		bool empty() const;

		void modify(size_t index, const f2Vec2& pos);
		void erase(size_t index);
		void insert(size_t index, const f2Vec2& pos);

		void pushBack(const f2Vec2& pos);
		void popBack();

	public:
		std::vector<f2Vec2> m_vertices;
		bool m_isLoop;

	}; // ChainShape
	
	inline size_t ChainShape::size() const
	{
		return m_vertices.size();
	}

	inline bool ChainShape::empty() const
	{
		return m_vertices.empty();
	}

	inline void ChainShape::modify(size_t index, const f2Vec2& pos)
	{
		m_vertices[index] = pos;
	}

	inline void ChainShape::erase(size_t index)
	{
		m_vertices.erase(m_vertices.begin() + index);
	}

	inline void ChainShape::insert(size_t index, const f2Vec2& pos)
	{
		m_vertices.insert(m_vertices.begin() + index, pos);
	}

	inline void ChainShape::pushBack(const f2Vec2& pos)
	{
		m_vertices.push_back(pos);
	}

	inline void ChainShape::popBack()
	{
		m_vertices.pop_back();
	}
}

#endif // _FEDITOR_CHAIN_SHAPE_H_