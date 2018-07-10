#ifndef _DBS_SHIP_H_
#define _DBS_SHIP_H_

#include "Doodle2D/doodle2d.h"

namespace dbs
{
	class Ship : public d2d::IDrawable
	{
	public:
		Ship(d2d::Context* pContext);

		//
		// d2d::IDrawable interface
		//
		virtual d2d::status load();
		virtual void draw() const;

		void spawn();
		void update();

	private:
		d2d::InputService* m_inputService;
		d2d::GraphicsService* m_graphicsService;
		d2d::TimeService* m_timeService;

		d2d::FrameAnimSprite* m_sprite;
// 		d2d::PhysicsObject::ptr m_physics;
// 		d2d::PhysicsTarget::ptr m_target;

	}; // Ship
}

#endif // _DBS_SHIP_H_