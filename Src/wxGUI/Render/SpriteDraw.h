#ifndef _WX_GUI_SPRITE_DRAW_H_
#define _WX_GUI_SPRITE_DRAW_H_

#include <Fruits2D/Fruits2D.h>

namespace wxgui
{
	class ISprite;
	class ISymbol;
	class SpriteBatch;

	class SpriteDraw
	{
	public:
		static void drawSprite(const ISprite* sprite);

		static void drawSprite(const ISymbol* symbol, const f2Vec2& pos,
			float angle = 0.0f, float scale = 1.0f);

		static void drawSprites(const std::vector<ISprite*>& sprites, 
			SpriteBatch& batch);

		static void begin(const ISprite* sprite);
		static void end(const ISprite* sprite);

	}; // SpriteDraw
}

#endif // _WX_GUI_SPRITE_DRAW_H_