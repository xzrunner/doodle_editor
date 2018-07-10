#include "ShapeCreator.h"
#include "Dataset/ChainShape.h"

using namespace FEDITOR;

Shape* ShapeCreator::arrow(const f2Vec2& pos, int dir, int length/* = 25*/, int width/* = 10*/)
{
	if (dir < 0 || dir > 3) return NULL;

	ChainShape* arrow = new ChainShape;
	switch (dir)
	{
	case 0:
		arrow->pushBack(f2Vec2(pos.x - width, pos.y - length));
		arrow->pushBack(pos);
		arrow->pushBack(f2Vec2(pos.x + width, pos.y - length));
		break;
	case 1:
		arrow->pushBack(f2Vec2(pos.x - width, pos.y + length));
		arrow->pushBack(pos);
		arrow->pushBack(f2Vec2(pos.x + width, pos.y + length));
		break;
	case 2:
		arrow->pushBack(f2Vec2(pos.x + length, pos.y + width));
		arrow->pushBack(pos);
		arrow->pushBack(f2Vec2(pos.x + length, pos.y - width));
		break;
	case 3:
		arrow->pushBack(f2Vec2(pos.x - length, pos.y + width));
		arrow->pushBack(pos);
		arrow->pushBack(f2Vec2(pos.x - length, pos.y - width));
		break;
	default:
		delete arrow;
		return NULL;
	}

	return arrow;
}