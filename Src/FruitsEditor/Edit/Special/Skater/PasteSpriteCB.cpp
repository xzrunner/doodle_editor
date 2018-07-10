#include "PasteSpriteCB.h"
#include "Utility.h"
#include "Dataset/Sprite.h"

using namespace FEDITOR;
using namespace FEDITOR::SKATER;

PasteSpriteCB::PasteSpriteCB(const BoundsContainer& bounds)
	: m_bounds(bounds)
{
}

void PasteSpriteCB::afterAddSprite(Sprite* sprite)
{
	addUserData(sprite);
	addSpriteBound(sprite);
}

void PasteSpriteCB::addUserData(Sprite* sprite)
{
	float* data = new float[4];
	data[0] = data[1] = 0.0f;
	data[2] = data[3] = 1.0f;
	sprite->setUserData(data);
}

void PasteSpriteCB::addSpriteBound(Sprite* sprite)
{
	Utility::addSpriteBound(sprite, m_bounds);
}