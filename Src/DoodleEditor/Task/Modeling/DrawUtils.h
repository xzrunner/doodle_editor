#ifndef _DEDITOR_MODELING_DRAW_UTILS_H_
#define _DEDITOR_MODELING_DRAW_UTILS_H_

#include <wxGUI/wxGUI.h>

#include "BodyData.h"

namespace deditor
{
	namespace modeling
	{
		class FixtureData;

		class DrawUtils
		{
		public:
			enum DrawType
			{
				e_default,
				e_mouseOn,
				e_selected
			};

		public:
			static void drawBody(BodyData* body, DrawType dType);
			static void drawFixture(FixtureData* fixture, DrawType dType,
				bool onlyFixture);

		private:
			static void getBodyColor(BodyData::Type type, DrawType dType,
				f2Colorf& cFace, f2Colorf& cEdge);
			static void getFixtureColor(DrawType type, f2Colorf& cFace, 
				f2Colorf& cEdge);

			static f2Colorf colorEnlarge(const f2Colorf& color, float factor);

		}; // DrawUtils
	}
}

#endif // _DEDITOR_MODELING_DRAW_UTILS_H_