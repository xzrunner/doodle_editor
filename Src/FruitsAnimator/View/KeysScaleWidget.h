#ifndef _FRUITS_ANIMATOR_KEYS_SCALE_WIDGET_H_
#define _FRUITS_ANIMATOR_KEYS_SCALE_WIDGET_H_
#include <wx/wx.h>

namespace FRUITS_ANIMATOR
{
	class KeysPanel;

	class KeysScaleWidget : public wxPanel
	{
	public:
		KeysScaleWidget(KeysPanel* parent, int id);

		void onSize(wxSizeEvent& event);
		void onPaint(wxPaintEvent& event);
		void onEraseBackground(wxEraseEvent& event);
		void onMouse(wxMouseEvent& event);

	private:
		int queryGridByPos(float x) const;

	private:
		static const int DIVISION_HEIGHT = 4;
		static const int TEXT_Y = 4;

	private:
		KeysPanel* m_parent;

		DECLARE_EVENT_TABLE()

	}; // KeysScaleWidget
}

#endif // _FRUITS_ANIMATOR_KEYS_SCALE_WIDGET_H_