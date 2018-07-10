#ifndef _FRUITS_ANIMATOR_SPRITE_FACTORY_H_
#define _FRUITS_ANIMATOR_SPRITE_FACTORY_H_

#include <Fruits2D/Fruits2D.h>

namespace FRUITS_ANIMATOR
{
	class Sprite;
	class Symbol;
	class WholeSkeleton;

	class SpriteFactory
	{
	public:
		enum SPRITE_TYPE
		{
			e_morphing = 0,
			e_skeletal
		};

	public:
		static Sprite* createSprite(SPRITE_TYPE type);

		static Sprite* createMorphingSprite(Symbol* symbol, const f2Vec2& pos, bool isCopyMesh);
		static Sprite* createSkeletalSprite(WholeSkeleton* skeleton);

	}; // SpriteFactory
}

#endif // _FRUITS_ANIMATOR_SPRITE_FACTORY_H_