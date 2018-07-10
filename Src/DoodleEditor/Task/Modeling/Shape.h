#ifndef _DEDITOR_MODELING_SHAPE_H_
#define _DEDITOR_MODELING_SHAPE_H_

#include <wxGUI/wxGUI.h>

namespace deditor
{
	namespace modeling
	{
		class IShape
		{
		public:
			enum Type
			{
				e_circle = 0,
				e_polygon
			};

		public:

			virtual ~IShape() {}
			
			virtual bool isContain(const f2Vec2& pos, 
				const f2Vec2& offset, float delta) const = 0;
			virtual bool isIntersect(const f2AABB& aabb,
				const f2Vec2& offset, float delta) const = 0;
			virtual void draw(const f2Colorf& cFace, const f2Colorf& cEdge) const = 0;

			Type getType() const { return m_type; }

		protected:
			Type m_type;

		}; // Shape

		class CircleShape : public IShape
		{
		public:
			CircleShape();

			virtual bool isContain(const f2Vec2& pos,
				const f2Vec2& offset, float delta) const;
			virtual bool isIntersect(const f2AABB& aabb,
				const f2Vec2& offset, float delta) const;
			virtual void draw(const f2Colorf& cFace, const f2Colorf& cEdge) const;

		public:
			f2Vec2 m_center;
			float m_radius;

		}; // CircleShape

		class PolygonShape : public IShape
		{
		public:
			PolygonShape();

			virtual bool isContain(const f2Vec2& pos,
				const f2Vec2& offset, float delta) const;
			virtual bool isIntersect(const f2AABB& aabb,
				const f2Vec2& offset, float delta) const;
			virtual void draw(const f2Colorf& cFace, const f2Colorf& cEdge) const;

		public:
			std::vector<f2Vec2> m_vertices;

		}; // PolygonShape
	}
}

#endif // _DEDITOR_MODELING_SHAPE_H_