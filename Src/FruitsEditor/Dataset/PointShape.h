#ifndef _FEDITOR_POINT_SHAPE_H_
#define _FEDITOR_POINT_SHAPE_H_
#include "Shape.h"

namespace FEDITOR
{
	class PointShape : public Shape
	{
	public:
		PointShape();
		PointShape(const PointShape& point);

		//
		// IObject interface
		//
		virtual PointShape* clone();

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

	public:
		f2Vec2 m_pos;

	}; // PointShape
}

#endif // _FEDITOR_POINT_SHAPE_H_