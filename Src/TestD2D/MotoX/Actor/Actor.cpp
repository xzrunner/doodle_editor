#include "Actor.h"
#include "ActorDefs.h"
#include "Motorbike.h"
#include "Player.h"
#include "DriveControl.h"
#include "ActorLoaderNew.h"

using namespace motox;

Actor::Actor(d2d::Context* pContext)
	: m_graphicsService(pContext->m_graphicsService)
	, m_physicsService(pContext->m_physicsService)
	, m_bike(NULL)
	, m_player(NULL)
	, m_batch(NULL)
{
	m_player = new Player(m_physicsService->getWorld());
 	m_bike = new Motorbike(pContext);

#ifdef D2D_ANDROID_NATIVE
	m_pApplication = pContext->m_pApplication;
#endif
}

Actor::~Actor()
{
 	delete m_player;
 	delete m_bike;
}

void Actor::load()
{
#ifdef D2D_WINDOWS
	ActorLoaderNew loader(this);
#elif defined D2D_ANDROID_NATIVE
	ActorLoaderNew loader(this, m_pApplication);
#elif defined D2D_ANDROID_JNI
	ActorLoaderNew loader(this);
#endif
}

void Actor::update()
{
 	m_player->update();
 	m_bike->update();
 
  	m_batch->lock();
  	int index = 0;
  	m_batch->add(*m_player->m_parts[e_PartBigLegLeft]->m_graphics, index++);
  	m_batch->add(*m_player->m_parts[e_PartSmallLegLeft]->m_graphics, index++);
  	m_batch->add(*m_player->m_parts[e_PartBigArmLeft]->m_graphics, index++);
  	m_batch->add(*m_player->m_parts[e_PartSmallArmLeft]->m_graphics, index++);
  	m_batch->add(*m_bike->m_backWheel->m_graphics, index++);
  	m_batch->add(*m_bike->m_frontWheel->m_graphics, index++);
  	m_batch->add(*m_bike->m_body->m_graphics, index++);
	m_batch->add(*m_bike->m_backDamping->m_graphics, index++);
	m_batch->add(*m_bike->m_frontDamping->m_graphics, index++);
  	m_batch->add(*m_player->m_parts[e_PartHead]->m_graphics, index++);
  	m_batch->add(*m_player->m_parts[e_PartBigLegRight]->m_graphics, index++);
  	m_batch->add(*m_player->m_parts[e_PartBody]->m_graphics, index++);
  	m_batch->add(*m_player->m_parts[e_PartSmallLegRight]->m_graphics, index++);
  	m_batch->add(*m_player->m_parts[e_PartBigArmRight]->m_graphics, index++);
  	m_batch->add(*m_player->m_parts[e_PartSmallArmRight]->m_graphics, index++);
  	m_batch->unlock();
}

void Actor::draw() const
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	m_batch->onDraw();

	glDisable(GL_BLEND);
}

void Actor::driving(bool* keyState)
{
	DriveControl control;
	control.tilt = DriveControl::MIDDLE;
	control.speed = DriveControl::BACK;

	if (keyState[e_left])
		control.tilt = DriveControl::LEFT;
	if (keyState[e_right])
		control.tilt = DriveControl::RIGHT;
	if (keyState[e_up])
		control.speed = DriveControl::FORWARD;
	if (keyState[e_down])
		control.speed = DriveControl::STOP;

	if (m_bike) m_bike->driving(control, m_settings);
	if (m_player) m_player->driving(control, m_settings);
}

void Actor::translate(const d2d::Vector& offset)
{
	const float dx = offset.x * d2d::BOX2D_SCALE_FACTOR_INVERSE,
		dy = offset.y * d2d::BOX2D_SCALE_FACTOR_INVERSE;

	if (m_player)
	{
		for (size_t i = 0; i < PLAYER_PARTS_COUNT; ++i)
		{
			b2Body* body = m_player->m_parts[i]->m_physics->getBody();
			b2Vec2 p(body->GetPosition());
			p.x += dx;
			p.y += dy;
			body->SetTransform(p, body->GetAngle());
		}
	}
	if (m_bike)
	{
		{
			b2Body* body = m_bike->m_frontWheel->m_physics->getBody();
			b2Vec2 p(body->GetPosition());
			p.x += dx;
			p.y += dy;
			body->SetTransform(p, body->GetAngle());
		}
		{
			b2Body* body = m_bike->m_backWheel->m_physics->getBody();
			b2Vec2 p(body->GetPosition());
			p.x += dx;
			p.y += dy;
			body->SetTransform(p, body->GetAngle());
		}
		{
			b2Body* body = m_bike->m_body->m_physics->getBody();
			b2Vec2 p(body->GetPosition());
			p.x += dx;
			p.y += dy;
			body->SetTransform(p, body->GetAngle());
		}
// 		{
// 			b2Body* body = m_bike->m_backDamping->m_physics->getBody();
// 			b2Vec2 p(body->GetPosition());
// 			p.x += dx;
// 			p.y += dy;
// 			body->SetTransform(p, body->GetAngle());
// 		}
	}
}

d2d::Vector Actor::getCenterPos() const
{
	d2d::Vector pos;
	if (m_bike)
	{
		b2Vec2 p = m_bike->m_body->m_physics->getBody()->GetPosition();
		pos.x = p.x * d2d::BOX2D_SCALE_FACTOR;
		pos.y = p.y * d2d::BOX2D_SCALE_FACTOR;

// 		b2Vec2 front = m_bike->m_frontWheel->m_physics->getBody()->GetPosition(),
// 			back = m_bike->m_backWheel->m_physics->getBody()->GetPosition();
//  		pos.x = (front.x + back.x) * 0.5f * d2d::BOX2D_SCALE_FACTOR;
//  		pos.y = (front.y + back.y) * 0.5f * d2d::BOX2D_SCALE_FACTOR;
	}
	else
	{
		pos.x = d2d::SCREEN_WIDTH >> 1;
		pos.y = d2d::SCREEN_HEIGHT >> 1;
	}
	return pos;
}