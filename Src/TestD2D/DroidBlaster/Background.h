#ifndef _DBS_BACKGROUND_H_
#define _DBS_BACKGROUND_H_

#include "Doodle2D/doodle2d.h"

namespace dbs
{
	class Background : public d2d::IDrawable
	{
	public:
		Background(d2d::Context* pContext);

		//
		// d2d::IDrawable interface
		//
		virtual d2d::status load();
		virtual void draw() const;

		void spawn();
		void update();

	private:
		d2d::TimeService* m_timeService;
		d2d::GraphicsService* m_graphicsService;
		d2d::TileMap* m_tileMap;
		d2d::Vector m_location; float m_animSpeed;

	}; // Background
}

#endif // _DBS_BACKGROUND_H_