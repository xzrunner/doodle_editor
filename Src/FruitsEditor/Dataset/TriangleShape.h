#ifndef _FEDITOR_TRIANGLE_SHAPE_H_
#define _FEDITOR_TRIANGLE_SHAPE_H_
#include "Shape.h"

namespace FEDITOR
{
	class TriangleShape : public Shape
	{
	public:
		TriangleShape();
		TriangleShape(const TriangleShape& triangle);

		//
		// IObject interface
		//
		virtual TriangleShape* clone();

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

		void setPos(const f2Vec2 pos[]);

	public:
		f2Vec2 m_pos[3];

	}; // TriangleShape

	inline void TriangleShape::setPos(const f2Vec2 pos[])
	{
		memcpy(&m_pos[0], &pos[0], sizeof(f2Vec2) * 3);
	}
}

#endif // _FEDITOR_TRIANGLE_SHAPE_H_