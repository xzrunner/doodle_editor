#include "SpriteFactory.h"
#include "MorphingSprite.h"
#include "SkeletalSprite.h"

using namespace FRUITS_ANIMATOR;

Sprite* SpriteFactory::createSprite(SPRITE_TYPE type)
{
	Sprite* sprite = NULL;
	switch (type)
	{
	case e_morphing:
		sprite = new MorphingSprite;
		break;
	case e_skeletal:
		sprite = new SkeletalSprite;
		break;
	}
	return sprite;
}

Sprite* SpriteFactory::createMorphingSprite(Symbol* symbol, const f2Vec2& pos, bool isCopyMesh)
{
	return new MorphingSprite(symbol, pos, isCopyMesh);
}

Sprite* SpriteFactory::createSkeletalSprite(WholeSkeleton* skeleton)
{
	return new SkeletalSprite(skeleton);
}