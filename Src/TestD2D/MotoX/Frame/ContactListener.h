#ifndef _MOOTOX_CONTACT_LISTENER_H_
#define _MOOTOX_CONTACT_LISTENER_H_

#include "Doodle2D/doodle2d.h"

#include <map>

namespace motox
{
	class ContactListener : public d2d::IContactListenerImpl
	{
	public:

		virtual void beginContact(b2Contact* contact);
		virtual void endContact(b2Contact* contact);
		virtual void preSolve(b2Contact* contact, const b2Manifold* oldManifold);
		virtual void postSolve(b2Contact* contact, const b2ContactImpulse* impulse);

	public:
		std::map<b2Body*, d2d::Vector> m_breakCache;

	}; // ContactListener
}

#endif // _MOOTOX_CONTACT_LISTENER_H_