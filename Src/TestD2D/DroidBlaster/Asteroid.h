#ifndef _DBS_ASTEROID_H_
#define _DBS_ASTEROID_H_

#include "Doodle2D/doodle2d.h"

#include <boost/shared_ptr.hpp>
#include <vector>

namespace dbs
{
	class Asteroid : public d2d::IDrawable
	{
	public:
		typedef boost::shared_ptr<Asteroid> ptr;
		typedef std::vector<ptr> vec;
		typedef vec::iterator vec_it;

	public:
		Asteroid(d2d::Context* pContext);

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

		d2d::FrameAnimSprite* m_sprite;
//		d2d::PhysicsObject::ptr m_physics;

	}; // Asteroid
}

#endif // _DBS_ASTEROID_H_