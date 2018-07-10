#ifndef _WX_GUI_SELECT_PIXELS_OP_H_
#define _WX_GUI_SELECT_PIXELS_OP_H_

#include "ZoomViewOP.h"
#include "Dataset/RawPixels.h"

namespace wxgui
{
	class SelectPixelsOP : public ZoomViewOP
	{
	public:
		enum e_Mode
		{
			RectSelect = 0,
			PointSelect,
			PolylineSelect
		};

	public:
		SelectPixelsOP(EditPanel* editPanel, RawPixels* pixels, e_Mode selectType, 
			RawPixels::PixelBuf& result, bool isSelect, int magicMarkerDis = 0);
		virtual ~SelectPixelsOP();

		virtual bool onMouseLeftDown(int x, int y);
		virtual bool onMouseLeftUp(int x, int y);
		virtual bool onMouseRightDown(int x, int y);
		virtual bool onMouseMove(int x, int y);
		virtual bool onMouseLeftDClick(int x, int y);
		virtual bool onMouseDrag(int x, int y);

		virtual bool onDraw() const;
		virtual bool clear();

		void setEditType(bool isSelect);
		void setMagicMarkerDis(int dis);

	private:
		void rectSelect();
		void pointSelect();
		void polylineSelect();

		void selectByPos(int x, int y);

		void selectByMagicMarker(int x, int y);

	private:
		RawPixels* m_pixels;

		bool m_isSelect;

		e_Mode m_mode;
		AbstractEditOP* m_drawOP;
		int m_magicMarkerDis;

		RawPixels::PixelBuf& m_result;
		
		f2Vec2 m_firstPos, m_currPos;
		std::vector<f2Vec2> m_area;

	}; // SelectPixelsOP
}

#endif // _WX_GUI_SELECT_PIXELS_OP_H_