#ifndef _DEDITOR_MOTOX_ACTOR_H_
#define _DEDITOR_MOTOX_ACTOR_H_

#include "ActorSettings.h"

#include <Doodle2D/doodle2d.h>

namespace motox
{
	class Motorbike;
	class Player;

	class Actor
	{
	public:
		Actor(d2d::Context* pContext);
		~Actor();

		void load();
		void update();
		void draw() const;

		void driving(bool* keyState);
		
		void translate(const d2d::Vector& offset);

		d2d::Vector getCenterPos() const;

// 		// todo
// 		d2d::SpriteBatch* getSpriteBatch() { return m_batch; }

	private:
		d2d::GraphicsService* m_graphicsService;
		d2d::PhysicsService* m_physicsService;

		ActorSettings m_settings;

		Motorbike* m_bike;
		Player* m_player;

		d2d::SpriteBatch* m_batch;

#ifdef D2D_ANDROID_NATIVE
		android_app* m_pApplication;
#endif

		friend class ActorLoaderNew;

	}; // Actor
}

#endif // _DEDITOR_MOTOX_ACTOR_H_