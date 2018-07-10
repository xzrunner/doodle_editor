#include "Sprite.h"

using namespace GAME_FRUITS::PREVIEW;

Sprite::Sprite(wxBitmap* bitmap, int x, int y)
{
	m_bitmap = bitmap;
	m_x = x;
	m_y = y;
}

void Sprite::onPaint(wxDC& dc) const
{
	dc.DrawBitmap(
		*m_bitmap,
		m_x - m_bitmap->GetWidth() * 0.5f,
		m_y - m_bitmap->GetHeight() * 0.5f
		);
}