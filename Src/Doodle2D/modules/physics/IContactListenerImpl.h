#ifndef _D2D_INTERFACE_CONTACT_LISTENER_IMPLEMENT_H_
#define _D2D_INTERFACE_CONTACT_LISTENER_IMPLEMENT_H_

namespace d2d
{
	class IContactListenerImpl
	{
	public:
		virtual void beginContact(b2Contact* contact) = 0;
		virtual void endContact(b2Contact* contact) = 0;
		virtual void preSolve(b2Contact* contact, const b2Manifold* oldManifold) = 0;
		virtual void postSolve(b2Contact* contact, const b2ContactImpulse* impulse) = 0;

	}; // IContactListenerImpl
}

#endif // _D2D_INTERFACE_CONTACT_LISTENER_IMPLEMENT_H_