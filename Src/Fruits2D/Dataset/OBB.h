#ifndef _F2D_OBB_H_
#define _F2D_OBB_H_
#include "AbstractBV.h"
#include "Fruits2D/Tools/f2Types.h"

namespace F2D
{
	class OBB : public AbstractBV
	{
	public:
		OBB();
		OBB(const OBB& obb);

		//
		// IObject interface
		//
		virtual OBB* clone();

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
		float getAngle() const;

	private:
		f2AABB transToAABB() const;

	private:
		f2AABB m_aabb;
		float m_angle;

	}; // OBB

	inline void OBB::initFromAABB(const f2AABB& aabb)
	{
		m_aabb = aabb;
		m_angle = 0;
	}

	inline bool OBB::isValid() const
	{
		return m_aabb.isValid();
	}

	inline void OBB::makeInfinite()
	{
		m_aabb.makeInfinite();
	}

	inline void OBB::combine(const f2Vec2& pos)
	{
		if (m_aabb.isValid())
		{
			m_aabb = transToAABB();
			m_angle = 0;
		}
		m_aabb.combine(pos);
	}

	inline void OBB::combine(const f2AABB& aabb)
	{
		if (m_aabb.isValid())
		{
			m_aabb = transToAABB();
			m_angle = 0;
		}
		m_aabb.combine(aabb);
	}

	inline const f2AABB& OBB::getAABB() const
	{
		return m_aabb;
	}

	inline float OBB::getAngle() const
	{
		return m_angle;
	}
}

#endif // _F2D_OBB_H_