#ifndef _DEDITOR_MODELING_FIXTURE_DATA_H_
#define _DEDITOR_MODELING_FIXTURE_DATA_H_

#include <wxGUI/wxGUI.h>

namespace deditor
{
	namespace modeling
	{
		class IShape;
		class BodyData;

		class FixtureData
		{
		public:
			FixtureData();
			~FixtureData();

			bool isContain(const f2Vec2& pos) const;
			bool isIntersect(const f2AABB& aabb) const;

			void draw(const f2Colorf& cFace, const f2Colorf& cEdge) const;

		public:
			wxString name;

			BodyData* body;

			IShape* shape;

			float density;

			float friction;
			float restitution;

			bool isSensor;

			unsigned short categoryBits;
			unsigned short maskBits;
			short groupIndex;

		}; // FixtureData
	}
}

#endif // _DEDITOR_MODELING_FIXTURE_DATA_H_