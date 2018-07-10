#include "PhysicsService.h"
#include "IContactListenerImpl.h"

#include "modules/timer/TimeService.h"
#include "common/Log.h"

using namespace d2d;

PhysicsService::PhysicsService(TimeService* pTimeService)
	: m_world(b2Vec2(0, -10.0f))
	, m_contactImpl(NULL)
	, m_bOpen(false)
{
	m_timeService = pTimeService;
	m_world.SetContactListener(this);

	m_world.SetContinuousPhysics(false);
}

status PhysicsService::update()
{
	if (!m_bOpen) return STATUS_OK;

 	// Updates simulation.
 	float lTimeStep = m_timeService->elapsed();
// 	Log::info("step: %f", lTimeStep);

//	lTimeStep = 0.03f;

	const float maxStep = 0.03f;
	if (lTimeStep > maxStep)
	{
	//	Log::info("**************************************************************************");

  		int count = lTimeStep / maxStep;
  		for (size_t i = 0; i < count; ++i)
  			m_world.Step(maxStep * 0.8f, VELOCITY_ITER, POSITION_ITER);
  		m_world.Step((lTimeStep - maxStep * count) * 0.8f, VELOCITY_ITER, POSITION_ITER);
		return STATUS_OK;
	}

#ifdef D2D_FRAME_RATE
	double start = m_timeService->now();
#endif // D2D_FRAME_RATE

	m_world.Step(lTimeStep, VELOCITY_ITER, POSITION_ITER);

#ifdef D2D_FRAME_RATE
	static double time = 0.0f, totTime = 0.0f;
	static int totFrame = 0;

	double cost = m_timeService->now() - start;
	if (cost > 0.5f)
	{
		time = totTime = 0;
		totFrame = 0;
		m_timeService->reset();
	}
	else
	{
		time += m_timeService->elapsed();
		totTime += cost;
		++totFrame;
		if (time > 1.0f)
		{
			d2d::Log::info("physics: %.0f", 1.0f * totFrame / totTime);
			time = 0.0f;
		}
	}
#endif // D2D_FRAME_RATE

	return STATUS_OK;
}

void PhysicsService::setContactImpl(IContactListenerImpl* impl)
{
	m_contactImpl = impl;
}

void PhysicsService::BeginContact(b2Contact* pContact)
{
	if (m_contactImpl)
		m_contactImpl->beginContact(pContact);
}

void PhysicsService::EndContact(b2Contact* contact)
{
	if (m_contactImpl)
		m_contactImpl->endContact(contact);
}

void PhysicsService::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
{
	if (m_contactImpl)
		m_contactImpl->preSolve(contact, oldManifold);
}

void PhysicsService::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse)
{
	if (m_contactImpl)
		m_contactImpl->postSolve(contact, impulse);
}
