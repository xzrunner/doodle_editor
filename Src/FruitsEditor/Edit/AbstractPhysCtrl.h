#ifndef _FEDITOR_ABSTRACT_PHYSICS_CONTROL_H_
#define _FEDITOR_ABSTRACT_PHYSICS_CONTROL_H_
#include "AbstractControl.h"
#include <Box2D/Box2D.h>
#include "../Render/b2Render.h"

namespace FEDITOR
{
	class PhysTaskSettingCmpt;

	class AbstractPhysCtrl : public b2ContactListener, public AbstractControl
	{
	public:
		AbstractPhysCtrl();
		virtual ~AbstractPhysCtrl();

		b2World* createWorld(const f2Vec2& gravity);

	protected:
		virtual void createEditCmpt();

		virtual void update();
		virtual void display() const;

		b2World* getWorld() const;

	private:
		void updatePhys();
		void displayPhys() const;

	private:
		b2World* m_world;

		DebugDraw m_debugDraw;

	protected:
		PhysTaskSettingCmpt* m_physSetting;

	}; // AbstractPhysCtrl

	inline b2World* AbstractPhysCtrl::getWorld() const
	{
		return m_world;
	}
}

#endif // _FEDITOR_ABSTRACT_PHYSICS_CONTROL_H_