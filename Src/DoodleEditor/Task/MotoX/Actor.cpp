#include "Actor.h"
#include "ActorDefs.h"
//#include "Motorbike.h"
#include "MotorbikeNew.h"
#include "Player.h"
#include "DriveControl.h"
#include "LibraryActorItem.h"
#include "Blackboard.h"

using namespace deditor::motox;

Actor::Actor(b2World* world, const LibraryActorItem& params)
	: m_params(params)
{
// 	m_bike = new Motorbike(world);
// 	m_bike->loadParts(params);

	m_bike = new MotorbikeNew(world);

	if (wxgui::FilenameTools::isExist(wxT("D:\\MyProject\\svn 2\\FruitsEditor\\MotoX\\MotoX\\editor\\zz\\2_modeling.txt")))
		m_bike->loadFromFile(wxT("D:\\MyProject\\svn 2\\FruitsEditor\\MotoX\\MotoX\\editor\\zz\\2_modeling.txt"));
	else
		m_bike->loadFromFile(wxT("2_modeling.txt"));

	m_player = new Player(world, m_bike->m_body);
	m_player->loadParts(params);
	setCollisionFilter();
}

Actor::~Actor()
{
	delete m_player;
	delete m_bike;
}

void Actor::load()
{
//	m_bike->loadJoints(m_params);
	m_bike->active();

	m_player->loadJoints(m_params);
}

void Actor::driving(bool* keyState)
{
	if (!m_player->m_bActive || !m_bike->m_bActive) return;

	DriveControl control;
	control.tilt = DriveControl::MIDDLE;
	control.speed = DriveControl::BACK;

	if (keyState['A' - 'A'])
		control.tilt = DriveControl::LEFT;
	if (keyState['D' - 'A'])
		control.tilt = DriveControl::RIGHT;

	if (keyState['W' - 'A'])
		control.speed = DriveControl::FORWARD;
	if (keyState['S' - 'A'])
		control.speed = DriveControl::STOP;

	if (m_bike) m_bike->driving(control, m_settings);
	if (m_player) m_player->driving(control, m_settings);
}

void Actor::update()
{
	for (size_t i = 0, n = PLAYER_PARTS_COUNT; i < n; ++i)
		m_player->m_parts[i]->updateEachFrame();

	m_bike->m_backWheel->updateEachFrame();
	m_bike->m_frontWheel->updateEachFrame();
	m_bike->m_body->updateEachFrame();
	m_bike->m_backDamping->updateEachFrame();
	m_bike->updateFrontDamping();
}

void Actor::setValue(int type, float val)
{
	switch (type)
	{
	case e_SetWheelFriction:
		if (m_bike) m_bike->m_backWheel->getBody()->setFriction(val);
		if (m_bike) m_bike->m_frontWheel->getBody()->setFriction(val);
		break;
	case e_SetMotoDensity:
		if (m_bike) m_bike->m_frontWheel->getBody()->setDensity(val);
		//		m_car->m_parts[Car::TYPE_BACK_WHEEL]->setDensity(val);
		//		m_car->m_parts[Car::TYPE_BODY]->setDensity(val);
		if (m_bike) m_bike->m_body->getBody()->getBody()->GetFixtureList()->GetNext()->SetDensity(val);
		break;
	case e_SetPlayerDensity:
		if (m_player)
		{
			for (size_t i = 0; i < PLAYER_PARTS_COUNT; ++i)
				m_player->m_parts[i]->getBody()->setDensity(val);
		}
		break;
	case e_SetSpeed:
		m_settings.maxSpeed = val;
		break;
	case e_SetAcc:
		m_settings.accSpeed = val;
		break;
	case e_SetTorque:
		m_settings.angularImpulse = val;
		break;
// 	case e_SetDamping:
// 		if (m_bike) m_bike->m_jointFront->SetSpringDampingRatio(val);
// 		if (m_bike) m_bike->m_jointBack->SetSpringDampingRatio(val);
// 		break;
// 	case e_SetHz:
// 		if (m_bike) m_bike->m_jointFront->SetSpringFrequencyHz(val);
// 		if (m_bike) m_bike->m_jointBack->SetSpringFrequencyHz(val);
// 		break;
 	case e_SetMaxMotorTorque:
 		if (m_bike) 
		{
			m_bike->m_backJoint->SetMaxMotorTorque(val);
			m_bike->m_frontJoint->SetMaxMotorTorque(val * Blackboard::frontWheelTorqueScale);
		}
 		break;
	}
}

void Actor::setLocation(const f2Vec2& pos)
{
	if (m_player)
	{
		for (size_t i = 0; i < PLAYER_PARTS_COUNT; ++i)
		{
			wxgui::ISprite* sprite = m_player->m_parts[i];
			sprite->setTransform(sprite->getPosition() + pos, sprite->getAngle());
		}
	}
	if (m_bike)
	{
		m_bike->m_frontWheel->setTransform(m_bike->m_frontWheel->getPosition() + pos, m_bike->m_frontWheel->getAngle());
		m_bike->m_backWheel->setTransform(m_bike->m_backWheel->getPosition() + pos, m_bike->m_backWheel->getAngle());
		m_bike->m_body->setTransform(m_bike->m_body->getPosition() + pos, m_bike->m_body->getAngle());
		m_bike->m_backDamping->setTransform(m_bike->m_backDamping->getPosition() + pos, m_bike->m_backDamping->getAngle());
	}

	const_cast<LibraryActorItem&>(m_params).setLocation(pos);
}

void Actor::onDraw() const
{
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

	wxgui::SpriteDraw::drawSprite(m_player->m_parts[e_PartBigLegLeft]);
	wxgui::SpriteDraw::drawSprite(m_player->m_parts[e_PartSmallLegLeft]);
	wxgui::SpriteDraw::drawSprite(m_player->m_parts[e_PartBigArmLeft]);
	wxgui::SpriteDraw::drawSprite(m_player->m_parts[e_PartSmallArmLeft]);

// 	wxgui::SpriteDraw::drawSprite(m_bike->m_frontWheel);
// 	wxgui::SpriteDraw::drawSprite(m_bike->m_backWheel);
// 	wxgui::SpriteDraw::drawSprite(m_bike->m_body);

 	wxgui::SpriteDraw::drawSprite(m_bike->m_frontWheel);
 	wxgui::SpriteDraw::drawSprite(m_bike->m_backWheel);
 	wxgui::SpriteDraw::drawSprite(m_bike->m_body);
	wxgui::SpriteDraw::drawSprite(m_bike->m_frontDamping);
	wxgui::SpriteDraw::drawSprite(m_bike->m_backDamping);

	wxgui::SpriteDraw::drawSprite(m_player->m_parts[e_PartHead]);
	wxgui::SpriteDraw::drawSprite(m_player->m_parts[e_PartBigLegRight]);
	wxgui::SpriteDraw::drawSprite(m_player->m_parts[e_PartBody]);
	wxgui::SpriteDraw::drawSprite(m_player->m_parts[e_PartSmallLegRight]);
	wxgui::SpriteDraw::drawSprite(m_player->m_parts[e_PartBigArmRight]);
	wxgui::SpriteDraw::drawSprite(m_player->m_parts[e_PartSmallArmRight]);
}

f2Vec2 Actor::getCenterPos() const
{
	f2Vec2 pos;
	if (m_bike)
	{
		b2Vec2 p = m_bike->m_body->getBody()->getBody()->GetPosition();
		pos.x = p.x * BOX2D_SCALE_FACTOR;
		pos.y = p.y * BOX2D_SCALE_FACTOR;
	}
	else
	{
		pos.x = 400.0f;
		pos.y = 240.0f;
	}
	return pos;
}

void Actor::getCollisionFilterSetting(b2Filter& motoFilter, b2Filter& playerCollFilter, 
									  b2Filter& playerNoCollFilter)
{
	motoFilter.categoryBits = MOTO_CATEGORY;
	motoFilter.maskBits = MOTO_MASK;
	motoFilter.groupIndex = MOTO_GROUP;

	playerCollFilter.maskBits = DEFAULT_MASK;
	playerNoCollFilter.categoryBits = PLAYER_CATEGORY;
	playerNoCollFilter.maskBits = PLAYER_MASK;
	playerCollFilter.groupIndex = playerNoCollFilter.groupIndex = PLAYER_GROUP;
}

void Actor::setCollisionFilter()
{
	b2Filter motoFilter, playerCollFilter, playerNoCollFilter;
	getCollisionFilterSetting(motoFilter, playerCollFilter, playerNoCollFilter);

	if (m_bike) m_bike->setCollisionFilter(motoFilter);
	if (m_player) m_player->setCollisionFilter(playerCollFilter, playerNoCollFilter);
}