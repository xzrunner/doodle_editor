#include "ArrangeSpriteCB.h"
#include "Utility.h"

using namespace FEDITOR;
using namespace FEDITOR::CHESSBOARD;

ArrangeSpriteCB::ArrangeSpriteCB(Layer* layer, Blackboard* blackboard)
{
	m_layer = layer;
	m_blackboard = blackboard;
	m_sprite = NULL;
}

void ArrangeSpriteCB::afterMoveSprite(Sprite* sprite)
{
	m_sprite = sprite;
}

void ArrangeSpriteCB::afterMouseLeftUp(const f2Vec2& pos)
{	
	if (m_sprite) Utility::fixSpritePos(m_sprite, m_layer, m_blackboard);
}