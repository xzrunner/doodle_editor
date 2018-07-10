#include "AEParts.h"
#include "LibraryActorItem.h"
#include "Actor.h"

using namespace deditor::motox;

const int AEParts::TRAVERSE_ORDER[PARTS_COUNT] = {
	e_PartBigLegLeft, e_PartSmallLegLeft,
	e_PartBigArmLeft, e_PartSmallArmLeft,
	e_PartFrontWheel, e_PartBackWheel, e_PartMotorBody,
	e_PartHead,
	e_PartBigLegRight, e_PartBody, e_PartSmallLegRight,
	e_PartBigArmRight, e_PartSmallArmRight
};

AEParts::AEParts(LibraryActorItem& params)
	: m_params(params)
{
	memset(m_parts, 0, sizeof(int) * PARTS_COUNT);
	initFromParams();
}

void AEParts::initFromParams()
{
	bool bComplete = true;
	for (size_t i = 0; i < PARTS_COUNT; ++i)
	{
		LibraryActorItem::PartDef& def = m_params.m_parts[i];
		if (def.path.IsEmpty())
		{
			bComplete = false;
			continue;
		}

		wxgui::ISymbol* symbol = wxgui::SymbolMgr::Instance()->getSymbol(def.path);
		if (m_parts[i]) 
			delete m_parts[i];
		m_parts[i] = wxgui::SpriteFactory::create(symbol);
		m_parts[i]->loadBodyFromFile();
		m_parts[i]->setTransform(def.pos, def.angle);
	}
	
	if (bComplete)
		setCollisionFilter();
}

void AEParts::traverse(IVisitor& visitor) const
{
	for (size_t i = 0; i < PARTS_COUNT; ++i)
	{
		if (!m_parts[TRAVERSE_ORDER[i]]) continue;

		bool hasNext;
		visitor.visit(m_parts[TRAVERSE_ORDER[i]], hasNext);
		if (!hasNext) break;
	}
}


void AEParts::loadPart(AEPartsCMPT::ID type, wxgui::ISymbol* symbol, const f2Vec2& pos)
{
	int part0, part1;
	mapCtrlIDToPartIDs(type, part0, part1);
	loadPart(part0, symbol, pos);
	if (part1 != -1) loadPart(part1, symbol, pos);
}

wxgui::ISprite* AEParts::getPart(int id)
{
	if (id >= 0 && id < PARTS_COUNT)
		return m_parts[id];
	else
		return NULL;
}

void AEParts::clear()
{
	for (size_t i = 0; i < PARTS_COUNT; ++i)
	{
		if (m_parts[i])
			m_parts[i]->release(), m_parts[i] = NULL;
	}
}

void AEParts::mapCtrlIDToPartIDs(AEPartsCMPT::ID ctrlID, int& partID0, int& partID1)
{
	partID0 = partID1 = -1;

	switch (ctrlID)
	{
	case AEPartsCMPT::e_Head:
		partID0 = e_PartHead;
		break;
	case AEPartsCMPT::e_Body:
		partID0 = e_PartBody;
		break;
	case AEPartsCMPT::e_BigArm:
		partID0 = e_PartBigArmLeft;
		partID1 = e_PartBigArmRight;
		break;
	case AEPartsCMPT::e_SmallArm:
		partID0 = e_PartSmallArmLeft;
		partID1 = e_PartSmallArmRight;
		break;
	case AEPartsCMPT::e_BigLeg:
		partID0 = e_PartBigLegLeft;
		partID1 = e_PartBigLegRight;
		break;
	case AEPartsCMPT::e_SmallLeg:
		partID0 = e_PartSmallLegLeft;
		partID1 = e_PartSmallLegRight;
		break;
	case AEPartsCMPT::e_FrontWheel:
		partID0 = e_PartFrontWheel;
		break;
	case AEPartsCMPT::e_BackWheel:
		partID0 = e_PartBackWheel;
		break;
	case AEPartsCMPT::e_Motorbike:
		partID0 = e_PartMotorBody;
		break;
	}
}

void AEParts::loadPart(int index, wxgui::ISymbol* symbol, const f2Vec2& pos)
{
	if (m_parts[index]) delete m_parts[index];

	wxgui::ISprite* sprite = wxgui::SpriteFactory::create(symbol);
	sprite->translate(pos);
	sprite->loadBodyFromFile();
	m_parts[index] = sprite;

	m_params.m_parts[index].path = symbol->getFilepath();
	m_params.m_parts[index].pos = pos;
	m_params.m_parts[index].angle = 0;

	setCollisionFilter(index);
}

void AEParts::setCollisionFilter(size_t part)
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

void AEParts::setCollisionFilter()
{
	b2Filter motoFilter, playerCollFilter, playerNoCollFilter;
	Actor::getCollisionFilterSetting(motoFilter, playerCollFilter, playerNoCollFilter);
	for (size_t i = 0; i < PARTS_COUNT; ++i)
	{
		if (i == e_PartHead || i == e_PartBody)
			m_parts[i]->getBody()->setCollisionFilter(playerCollFilter);
		else if (i >= e_PartBigArmLeft && i <= e_PartSmallLegRight)
			m_parts[i]->getBody()->setCollisionFilter(playerNoCollFilter);
		else if (i >= e_PartFrontWheel && i <= e_PartMotorBody)
			m_parts[i]->getBody()->setCollisionFilter(motoFilter);
	}
}