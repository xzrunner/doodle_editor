#ifndef _DEDITOR_MODELING_BODY_DATA_H_
#define _DEDITOR_MODELING_BODY_DATA_H_

#include <wxGUI/wxGUI.h>

namespace deditor
{
	namespace modeling
	{
		class FixtureData;

		class BodyData : public IObject
		{
		public:
			enum Type
			{
				e_static = 0,
				e_kinematic,
				e_dynamic
			};

		public:
			BodyData();
			~BodyData();

			virtual BodyData* clone() { return NULL; }

			bool isContain(const f2Vec2& pos) const;
			bool isIntersect(const f2AABB& aabb) const;

			void draw(const f2Colorf& cFace, const f2Colorf& cEdge) const;

		public:
			wxString m_name;

			Type m_type;

			float m_gravityScale;

			wxgui::ISprite* m_sprite;

			std::vector<FixtureData*> m_fixtures;

		}; // BodyData
	}
}

#endif // _DEDITOR_MODELING_BODY_DATA_H_