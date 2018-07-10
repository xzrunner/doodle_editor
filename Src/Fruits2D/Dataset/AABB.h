#ifndef _F2D_AABB_H_
#define _F2D_AABB_H_
#include "AbstractBV.h"
#include "Fruits2D/Tools/f2Types.h"

namespace F2D
{
	class AABB : public AbstractBV
	{
	public:
		AABB();
		AABB(const AABB& aabb);

		//
		// IObject interface
		//
		virtual AABB* clone();

		//
		// ISerializable interface
		//
		virtual void loadFromTextFile(std::ifstream& fin);
		virtual void storeToTextFile(std::ofstream& fout) const;

		virtual void initFromAABB(const f2AABB& aabb);

		virtual bool isValid() const;
		virtual void makeInfinite();

		virtual void translate(const f2Vec2& offset);
		virtual void rotate(float delta);

		virtual void combine(const f2Vec2& pos);
		virtual void combine(const f2AABB& aabb);

		virtual bool isContain(const f2Vec2& pos) const;
		virtual bool isIntersect(const f2AABB& aabb) const;
		
		virtual float area() const;
		virtual float width() const;
		virtual float height() const;
		virtual f2Vec2 center() const;

		virtual void getBoundPos(std::vector<f2Vec2>& bound) const;

		const f2AABB& getAABB() const;

	private:
		f2AABB m_aabb;

	}; // AABB

	inline void AABB::initFromAABB(const f2AABB& aabb)
	{
		m_aabb = aabb;
	}

	inline bool AABB::isValid() const
	{
		return m_aabb.isValid();
	}

	inline void AABB::makeInfinite()
	{
		m_aabb.makeInfinite();
	}

	inline void AABB::translate(const f2Vec2& offset)
	{
		m_aabb.translate(offset);
	}

	inline void AABB::rotate(float delta)
	{
		m_aabb.makeInfinite();
	}

	inline void AABB::combine(const f2Vec2& pos)
	{
		m_aabb.combine(pos);
	}

	inline void AABB::combine(const f2AABB& aabb)
	{
		m_aabb.combine(aabb);
	}

	inline const f2AABB& AABB::getAABB() const
	{
		return m_aabb;
	}
}

#endif // _F2D_AABB_H_