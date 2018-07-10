#include "ContactListener.h"
#include "TypesDef.h"
#include "Model.h"
#include "Blackboard.h"
#include "Dataset/Sprite.h"

using namespace FEDITOR::MOTOX::LEVEL;

ContactListener::ContactListener(Model* model, Blackboard* blackboard)
{
	m_model = model;
	m_blackboard = blackboard;
}

void ContactListener::BeginContact(b2Contact* contact)
{
	if (!m_blackboard->m_stopInstant) return;

	b2Fixture* fixtureA = contact->GetFixtureA();
	b2Fixture* fixtureB = contact->GetFixtureB();

	void *userDataA = fixtureA->GetBody()->GetUserData(),
		*userDataB = fixtureB->GetBody()->GetUserData();
	if (userDataA && userDataB)
	{
		int *flagA = (int*) userDataA,
			*flagB = (int*) userDataB;
		if (*flagA == e_TrackChain && *flagB == e_Stone)
		{
//			fixtureB->GetBody()->SetActive(false);
//			fixtureB->GetBody()->SetLinearVelocity(b2Vec2(0, 0));
//			deleteBody(fixtureB->GetBody());

			m_buffer.push_back(fixtureB->GetBody());
		}
		else if (*flagB == e_TrackChain && *flagA == e_Stone)
		{
//			fixtureA->GetBody()->SetActive(false);
//			fixtureB->GetBody()->SetLinearVelocity(b2Vec2(0, 0));
//			deleteBody(fixtureA->GetBody());

			m_buffer.push_back(fixtureA->GetBody());
		}
	}
}

void ContactListener::deletePhysics()
{
	for (size_t i = 0, n = m_buffer.size(); i < n; ++i)
		deleteBody(m_buffer[i]);
	m_buffer.clear();
}

void ContactListener::deleteBody(b2Body* body)
{
	Sprite* sprite = m_model->querySpriteByBody(body);
	if (sprite)
	{
		m_model->eraseFromBodySpriteMap(body);
		sprite->setBody(NULL);
	}
}