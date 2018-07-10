#include "Utility.h"
#include "Blackboard.h"
#include "Dataset/Sprite.h"
#include "Dataset/Layer.h"

using namespace FEDITOR;
using namespace FEDITOR::MONSTER;

void Utility::fixSpritePos(Sprite* sprite, Layer* layer, Blackboard* blackboard)
{
	const f2Vec2& pos = sprite->getPosition();

	if (pos.x < 0 || pos.x > blackboard->m_edge * Blackboard::COL ||
		pos.y < - blackboard->m_edge * Blackboard::ROW || pos.y > blackboard->m_edge * blackboard->m_length)
	{
		layer->deleteSprite(sprite);
	}
	else
	{
		float* data = static_cast<float*>(sprite->getUserData());
		if (data == NULL)
		{
			data = new float[3];
			data[2] = -1;
			sprite->setUserData(data);
		}

		if (pos.y < 0)
		{
			const int col = (int) ((sprite->getPosition().x - 0.0f) / blackboard->m_edge),
				row = (int) ((0.0f - sprite->getPosition().y) / blackboard->m_edge);
			const float x = col * blackboard->m_edge + blackboard->m_edge * 0.5f,
				y =  - row * blackboard->m_edge - blackboard->m_edge * 0.5f;
			sprite->setTransform(f2Vec2(x, y), sprite->getAngle());

			data[0] = col + 1;
			data[1] = - (row + 1);

			eraseSamePosUnderground(layer, data[0], data[1], sprite);
		}
		else
		{
			const int col = (int) ((sprite->getPosition().x - 0.0f) / blackboard->m_edge);
			const float x = col * blackboard->m_edge + blackboard->m_edge * 0.5f;
			sprite->setTransform(f2Vec2(x, sprite->getPosition().y), sprite->getAngle());

			data[0] = col + 1;
			data[1] = sprite->getPosition().y / (blackboard->m_edge * blackboard->m_length);
		}
	}
}

void Utility::eraseSamePosUnderground(Layer* layer, float d0, float d1, Sprite* except)
{
	std::vector<Sprite*> buffer;

	const std::vector<Sprite*>& sprites = layer->getAllSprites();
	for (size_t i = 0, n = sprites.size(); i < n; ++i)
	{
		Sprite* sprite = sprites[i];
		if (sprite == except) continue;

		float* data = static_cast<float*>(sprite->getUserData());
		if (data[0] == d0 && data[1] == d1)
			buffer.push_back(sprite);
	}

	for (size_t i = 0, n = buffer.size(); i < n; ++i)
		layer->deleteSprite(buffer[i]);
}