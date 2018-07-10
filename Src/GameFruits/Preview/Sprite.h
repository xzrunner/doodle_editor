#ifndef _GAME_FRUITS_PREVIEW_SPRITE_H_
#define _GAME_FRUITS_PREVIEW_SPRITE_H_
#include <wx/wx.h>

namespace GAME_FRUITS
{
	namespace PREVIEW
	{
		class Sprite
		{
		public:
			Sprite(wxBitmap* bitmap, int x, int y);

			void onPaint(wxDC& dc) const;

		private:
			wxBitmap* m_bitmap;
			int m_x, m_y;

		}; // Sprite
	}
}

#endif // _GAME_FRUITS_PREVIEW_SPRITE_H_