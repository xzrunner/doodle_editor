#include "AbstractPhysCtrl.h"
#include "AbstractView.h"
#include "EditComponent/PhysTaskSettingCmpt.h"

using namespace FEDITOR;

AbstractPhysCtrl::AbstractPhysCtrl()
{
	m_world = createWorld(f2Vec2(0.0f, -10.0f));

	uint32 flags = 0;
	flags += b2Draw::e_shapeBit;
	flags += b2Draw::e_jointBit;
	m_debugDraw.SetFlags(flags);
}

AbstractPhysCtrl::~AbstractPhysCtrl()
{
}

b2World* AbstractPhysCtrl::createWorld(const f2Vec2& gravity)
{
	b2World* world;

	b2Vec2 b2gravity;
	b2gravity.Set(gravity.x, gravity.y);
	world = new b2World(b2gravity);

	world->SetContactListener(this);
	world->SetDebugDraw(&m_debugDraw);

	return world;
}

void AbstractPhysCtrl::createEditCmpt()
{
	m_physSetting = new PhysTaskSettingCmpt(m_view->getCmptMgr());
}

void AbstractPhysCtrl::update()
{
	AbstractControl::update();
	updatePhys();
}

void AbstractPhysCtrl::display() const
{
	AbstractControl::display();
	displayPhys();
}

void AbstractPhysCtrl::updatePhys()
{
	if (m_physSetting->isStepOpen())
	{
		const float timeStep = 1.0f / m_physSetting->getHz();
		m_world->Step(timeStep, m_physSetting->getVelocityIterations(), m_physSetting->getPositionIterations());
	}
}

void AbstractPhysCtrl::displayPhys() const
{
	if (m_physSetting->isDrawOpen())
	{
		m_world->DrawDebugData();
	}
}