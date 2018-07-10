#ifndef _WX_GUI_BODY_FACTORY_H_
#define _WX_GUI_BODY_FACTORY_H_

#include "FixtureData.h"

#include <wx/wx.h>
#include <Fruits2D/Fruits2D.h>

class b2World;

namespace wxgui
{
	class IBody;

	class BodyFactory
	{
	public:
		static IBody* createBody(const wxString& filename, float scale = 1.0f);
		static IBody* createBody(const std::vector<f2Vec2>& triangles, float scale = 1.0f);
		static IBody* createBody(const std::vector<FixtureDataInfo>& fixtures, float scale = 1.0f);

		static void setWorld(b2World* world);

	private:
		static b2World* m_world;

	}; // BodyFactory

	inline void BodyFactory::setWorld(b2World* world)
	{
		m_world = world;
	}
}

#endif // _WX_GUI_BODY_FACTORY_H_