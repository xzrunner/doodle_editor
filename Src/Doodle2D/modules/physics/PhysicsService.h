#ifndef _D2D_PHYSICS_SERVICE_H_
#define _D2D_PHYSICS_SERVICE_H_

#include "common/Types.h"

#include <Box2D/Box2D.h>

namespace d2d
{
	class TimeService;
	class IContactListenerImpl;

	class PhysicsService : public b2ContactListener
	{
	public:
		PhysicsService(TimeService* pTimeService);

		status update();

		// todo
		b2World* getWorld() { return &m_world; }
		//

		void setContactImpl(IContactListenerImpl* impl);

 		void open(bool bOpen) {
			m_bOpen = bOpen;
			if (m_bOpen)
				m_world.ClearForces();
 		}

	private:
		void BeginContact(b2Contact* contact);
		void EndContact(b2Contact* contact);
		void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);
		void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);

	private:
		TimeService* m_timeService;
		b2World m_world;

		IContactListenerImpl* m_contactImpl;

		bool m_bOpen;

		static const int32_t VELOCITY_ITER = 6;
		static const int32_t POSITION_ITER = 2;

	}; // PhysicsService
}

#endif // _D2D_PHYSICS_SERVICE_H_