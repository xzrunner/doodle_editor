#include "Utility.h"
#include "Blackboard.h"
#include "Dataset/Sprite.h"
#include "Dataset/Layer.h"

using namespace FEDITOR;
using namespace FEDITOR::CHESSBOARD;

void Utility::fixSpritePos(Sprite* sprite, Layer* layer, Blackboard* blackboard)
{
	const f2Vec2& pos = sprite->getPosition();
	if (pos.x < 0 || pos.x > blackboard->m_edge * blackboard->m_col ||
		pos.y < 0 || pos.y > blackboard->m_edge * blackboard->m_row)
	{
		layer->deleteSprite(sprite);
	}
	else
	{
		const int col = (int) ((sprite->getPosition().x - 0.0f) / blackboard->m_edge),
			row = (int) ((sprite->getPosition().y - 0.0f) / blackboard->m_edge);
		const float x = col * blackboard->m_edge + blackboard->m_edge * 0.5f,
			y = row * blackboard->m_edge + blackboard->m_edge * 0.5f;
		sprite->setTransform(f2Vec2(x, y), sprite->getAngle());

		int* data = new int[2];
		data[0] = col + 1;
		data[1] = row + 1;
		sprite->setUserData(data);
	}
}