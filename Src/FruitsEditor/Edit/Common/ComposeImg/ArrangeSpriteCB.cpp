#include "ArrangeSpriteCB.h"
#include "Dataset/Sprite.h"
#include "Edit/EditComponent/CoordinateAxesCmpt.h"

using namespace FEDITOR;
using namespace FEDITOR::COMPOSE_IMG;

ArrangeSpriteCB::ArrangeSpriteCB(CoordinateAxesCmpt* coordsCmpt)
{
	m_coordsCmpt = coordsCmpt;
}

void ArrangeSpriteCB::afterMoveSprite(Sprite* sprite)
{
	std::cout << m_coordsCmpt->transToCurrCoordinate(sprite->getPosition()) << std::endl;
}