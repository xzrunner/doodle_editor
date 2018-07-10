#ifndef _FRUITS_ANIMATOR_RENDER_H_
#define _FRUITS_ANIMATOR_RENDER_H_
#include <wxGUI/wxGUI.h>

namespace FRUITS_ANIMATOR
{
	class Sprite;

	class Render
	{
	public:
		static void drawPos(const f2Vec2& pos, float radius);

		static void drawSprites(const std::vector<Sprite*>& sprites);
		static void drawSpriteCenter(Sprite* sprite);
		static void drawSpriteCenterMesh(Sprite* sprite);
		static void drawSpriteCenterPartSkeleton(Sprite* sprite);
		static void drawSpriteCenterWholeSkeleton(Sprite* sprite);

		static void drawRawPixels(const wxgui::RawPixels& pixels);
		static void drawRawPixelsBound(const wxgui::RawPixels& pixels);
		static void drawRawPixelsSelected(const wxgui::RawPixels& original, const wxgui::RawPixels::PixelBuf& selected);
		static void drawRawPixelsSelectedFlag(const wxgui::RawPixels& original, const wxgui::RawPixels::PixelBuf& selected);

	}; // Render
}

#endif // _FRUITS_ANIMATOR_RENDER_H_