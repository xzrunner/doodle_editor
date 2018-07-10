#include "ContactListener.h"

#include "Tools/connect_id_defs.h"

using namespace motox;

void ContactListener::beginContact(b2Contact* contact)
{

}

void ContactListener::endContact(b2Contact* contact)
{

}

void ContactListener::preSolve(b2Contact* contact, const b2Manifold* oldManifold)
{
	b2Fixture* fixtureA = contact->GetFixtureA();
	b2Fixture* fixtureB = contact->GetFixtureB();

	void* dataA = fixtureA->GetBody()->GetUserData();
	void* dataB = fixtureB->GetBody()->GetUserData();
	if (dataA && dataB)
	{
		int idA = *static_cast<int*>(dataA);
		int idB = *static_cast<int*>(dataB);

  		//if (idA == PIECE_ID && idB == PIECE_ID)
  		//{
  		//	contact->SetEnabled(false);
  		//}
  		if (idA == ACTOR_ID && idB == PIECE_ID
  			|| idA == PIECE_ID && idB == ACTOR_ID
  			|| idA == PIECE_ID && idB == PIECE_ID)
  		{
  			contact->SetEnabled(false);
  		}
	}
}

void ContactListener::postSolve(b2Contact* contact, const b2ContactImpulse* impulse)
{
	float32 maxImpulse = 0.0f;
	b2Vec2 maxPos;

	int32 count = contact->GetManifold()->pointCount;
	for (int32 i = 0; i < count; ++i)
	{
		if (impulse->normalImpulses[i] > maxImpulse)
		{
			maxImpulse = impulse->normalImpulses[i];
			maxPos = contact->GetManifold()->points[i].localPoint;
		}
	}

	if (maxImpulse < 20.0f)
		return;

	d2d::Vector pos;
	pos.x = maxPos.x * d2d::BOX2D_SCALE_FACTOR;
	pos.y = maxPos.y * d2d::BOX2D_SCALE_FACTOR;

	b2Fixture* fixtureA = contact->GetFixtureA();
	b2Fixture* fixtureB = contact->GetFixtureB();

	void* dataA = fixtureA->GetBody()->GetUserData();
	void* dataB = fixtureB->GetBody()->GetUserData();
	if (dataA && dataB)
	{
		int idA = *static_cast<int*>(dataA);
		int idB = *static_cast<int*>(dataB);
		if (idA == BREAKABLE_ID)
			m_breakCache.insert(std::make_pair(fixtureA->GetBody(), pos));
		else if (idB == BREAKABLE_ID)
			m_breakCache.insert(std::make_pair(fixtureB->GetBody(), pos));
	}
}