#ifndef _WX_GUI_ARRANGE_SPRITE_ATOMIC_OP_H_
#define _WX_GUI_ARRANGE_SPRITE_ATOMIC_OP_H_

#include "AbstractAtomicOP.h"
#include "Dataset/SelectionSet.h"

namespace wxgui
{
	class MultiSpritesImpl;

	namespace arrange_sprite
	{
		class SpritesAOP : public AbstractAtomicOP
		{
		public:
			SpritesAOP(const SpriteSelection& selection);
			SpritesAOP(const std::vector<ISprite*>& sprites);
			virtual ~SpritesAOP();

		protected:
			std::vector<ISprite*> m_sprites;

		}; // SpritesAOP

		class MoveSpritesAOP : public SpritesAOP
		{
		public:
			MoveSpritesAOP(const SpriteSelection& selection, const f2Vec2& offset);
			MoveSpritesAOP(const std::vector<ISprite*>& sprites, const f2Vec2& offset);

			virtual void undo();
			virtual void redo();

		private:
			f2Vec2 m_offset;

		}; // MoveSpritesAOP

		class RotateSpritesAOP : public SpritesAOP
		{
		public:
			RotateSpritesAOP(const SpriteSelection& selection, const f2Vec2& start, const f2Vec2& end);
			RotateSpritesAOP(const std::vector<ISprite*>& sprites, const f2Vec2& start, const f2Vec2& end);

			virtual void undo();
			virtual void redo();

		private:
			f2Vec2 m_start, m_end;

		}; // RotateSpritesAOP

		class DeleteSpritesAOP : public SpritesAOP
		{
		public:
			DeleteSpritesAOP(const SpriteSelection& selection, MultiSpritesImpl* spritesImpl);
			DeleteSpritesAOP(const std::vector<ISprite*>& sprites, MultiSpritesImpl* spritesImpl);

			virtual void undo();
			virtual void redo();

		private:
			MultiSpritesImpl* m_spritesImpl;

		}; // DeleteSpritesAOP
	}
}

#endif // _WX_GUI_ARRANGE_SPRITE_ATOMIC_OP_H_