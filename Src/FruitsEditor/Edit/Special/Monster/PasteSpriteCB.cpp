#include "PasteSpriteCB.h"
#include "Utility.h"

using namespace FEDITOR;
using namespace FEDITOR::MONSTER;

PasteSpriteCB::PasteSpriteCB(Layer* layer, Blackboard* blackboard)
{
	m_layer = layer;
	m_blackboard = blackboard;
}

void PasteSpriteCB::afterAddSprite(Sprite* sprite)
{
	Utility::fixSpritePos(sprite, m_layer, m_blackboard);
}