#ifndef _WX_GUI_BITMAP_H_
#define _WX_GUI_BITMAP_H_

#include "Tools/ResourcesMgr.h"

#include <wx/wx.h>

namespace wxgui
{
	class Bitmap;
	typedef ResourcesMgr<Bitmap> BitmapMgr;

	class Bitmap
	{
	public:
		Bitmap();
		Bitmap(wxBitmap* bitmap);
		virtual ~Bitmap();

		bool loadFromFile(const wxString& filepath);

		const wxBitmap* getBitmap() const {
			return m_bitmap;
		}

	private:
		static float computeScale(float width);

	private:
		wxBitmap* m_bitmap;

		float m_scale;

	}; // Bitmap
}

#endif // _WX_GUI_BITMAP_H_