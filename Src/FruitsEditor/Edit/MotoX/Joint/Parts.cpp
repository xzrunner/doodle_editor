#include "Parts.h"
#include "Blackboard.h"
#include "../Utility.h"
#include "../Actor.h"
#include "../../../Dataset/Sprite.h"
#include "../../../Dataset/Layer.h"
#include "../../../File/ActorMotionAdapter.h"
#include <Box2D/Box2D.h>

using namespace FEDITOR;
using namespace FEDITOR::MOTOX::JOINT;

const int Parts::PARTS_ORDER[PARTS_COUNT] = {
	MOTOX::e_PartBigLegLeft, MOTOX::e_PartSmallLegLeft,
	MOTOX::e_PartBigArmLeft, MOTOX::e_PartSmallArmLeft,
	MOTOX::e_PartFrontWheel, MOTOX::e_PartBackWheel, MOTOX::e_PartMotorBody,
	MOTOX::e_PartHead, MOTOX::e_PartBody,
	MOTOX::e_PartBigLegRight, MOTOX::e_PartSmallLegRight,
	MOTOX::e_PartBigArmRight, MOTOX::e_PartSmallArmRight
};

Parts::Parts()
{
	memset(m_parts, 0, sizeof(int) * PARTS_COUNT);
}

void Parts::loadFromTextFile(std::ifstream& fin)
{
	for (size_t i = 0; i < PARTS_COUNT; ++i)
		loadPartFromTextFile(fin, i);
}

void Parts::storeToTextFile(std::ofstream& fout) const
{
	for (size_t i = 0; i < PARTS_COUNT; ++i)
		storePartToTextFile(fout, i);
}

void Parts::loadFromFileAdapter(const ActorMotionAdapter& adapter)
{
	for (size_t i = 0; i < PARTS_COUNT; ++i)
	{
		const ActorMotionAdapter::Part& part = adapter.m_parts[i];
		m_parts[i]->loadFromUnknownFile(part.filename);
		m_parts[i]->setTransform(part.pos, part.angle);
		setCollisionFilter(i);
	}
}

void Parts::initSprites(Layer* layer)
{
	for (size_t i = 0; i < PARTS_COUNT; ++i)
	{
		m_parts[PARTS_ORDER[i]] = new Sprite(MOTOX::SCALE_SCREEN_TO_PHYSICS);
		layer->addSprite(m_parts[PARTS_ORDER[i]]);
	}
}

void Parts::loadPartTypeFromFile(size_t type, const std::string& filename)
{
	switch (type)
	{
	case Blackboard::e_OpenHead:
		loadPartFromFile(e_PartHead, filename);
		break;
	case Blackboard::e_OpenBody:
		loadPartFromFile(e_PartBody, filename);
		break;
	case Blackboard::e_OpenBigArm:
		loadPartFromFile(e_PartBigArmLeft, filename);
		loadPartFromFile(e_PartBigArmRight, filename);
		break;
	case Blackboard::e_OpenSmallArm:
		loadPartFromFile(e_PartSmallArmLeft, filename);
		loadPartFromFile(e_PartSmallArmRight, filename);
		break;
	case Blackboard::e_OpenBigLeg:
		loadPartFromFile(e_PartBigLegLeft, filename);
		loadPartFromFile(e_PartBigLegRight, filename);
		break;
	case Blackboard::e_OpenSmallLeg:
		loadPartFromFile(e_PartSmallLegLeft, filename);
		loadPartFromFile(e_PartSmallLegRight, filename);
		break;
	case Blackboard::e_OpenFrontWheel:
		loadPartFromFile(e_PartFrontWheel, filename);
		break;
	case Blackboard::e_OpenBackWheel:
		loadPartFromFile(e_PartBackWheel, filename);
		break;
	case Blackboard::e_OpenMotorbike:
		loadPartFromFile(e_PartMotorBody, filename);
		break;
	}
}

void Parts::setAlive(bool isAlive)
{
	for (size_t i = 0; i < PARTS_COUNT; ++i)
	{
		Body* body = m_parts[i]->getBody();
		if (body) body->setAlive(isAlive);
	}
}

void Parts::loadPartFromTextFile(std::ifstream& fin, size_t part)
{
	std::string filename;
	f2Vec2 pos;
	float angle;
	fin >> filename >> pos >> angle;
	m_parts[part]->loadFromUnknownFile(filename);
	m_parts[part]->setTransform(pos, angle);
	setCollisionFilter(part);
}

void Parts::storePartToTextFile(std::ofstream& fout, size_t part) const
{
	Sprite* sprite = m_parts[part];
	assert(sprite);
	fout << sprite->getBody()->getFilename() << '\n'
		<< sprite->getPosition() << " " << sprite->getAngle() << '\n';
}

void Parts::loadPartFromFile(size_t part, const std::string& filename)
{
	m_parts[part]->loadFromUnknownFile(filename);
	setCollisionFilter(part);
}

void Parts::setCollisionFilter(size_t part)
{
	b2Filter motoFilter, playerCollFilter, playerNoCollFilter;
	Actor::getCollisionFilterSetting(motoFilter, playerCollFilter, playerNoCollFilter);
	if (part == e_PartHead || part == e_PartBody)
		m_parts[part]->getBody()->setCollisionFilter(playerCollFilter);
	else if (part >= e_PartBigArmLeft && part <= e_PartSmallLegRight)
		m_parts[part]->getBody()->setCollisionFilter(playerNoCollFilter);
	else if (part >= e_PartFrontWheel && part <= e_PartMotorBody)
		m_parts[part]->getBody()->setCollisionFilter(motoFilter);
}