#include "ArrangeSpriteCB.h"
#include "Parts.h"
#include "../ActorDefs.h"
#include "../../../Dataset/Sprite.h"

using namespace FEDITOR;
using namespace FEDITOR::MOTOX::JOINT;

ArrangeSpriteCB::ArrangeSpriteCB(Parts& parts)
	: m_parts(parts)
{
}

void ArrangeSpriteCB::afterMoveSprite(Sprite* sprite)
{
	int id = -1;
	for (int i = e_PartBigArmLeft; i <= e_PartSmallLegRight; ++i)
		if (m_parts.getPart(i) == sprite) id = i;
	if (id != -1)
	{
		Sprite *src = m_parts.getPart(id), *dst;
		if (id % 2 == 0) dst = m_parts.getPart(id + 1);
		else dst = m_parts.getPart(id - 1);
		dst->setTransform(src->getPosition(), src->getAngle());
	}

	if (sprite == m_parts.getPart(e_PartMotorBody))
		sprite->setTransform(f2Vec2(0, 0), 0);
}