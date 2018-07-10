#ifndef _FRUITS_ANIMATOR_LAYERS_CONTENT_WIDGET_H_
#define _FRUITS_ANIMATOR_LAYERS_CONTENT_WIDGET_H_
#include <wx/wx.h>

namespace FRUITS_ANIMATOR
{
	class LayersPanel;
	class LayersMgr;

	class LayersContentWidget : public wxPanel
	{
	public:
		LayersContentWidget(LayersPanel* parent, int id, LayersMgr* layersMgr);

		virtual wxCoord OnGetRowHeight(size_t row) const;

		virtual int GetNonOrientationTargetSize() const;
		virtual wxOrientation GetOrientation() const;

		void onSize(wxSizeEvent& event);
		void onPaint(wxPaintEvent& event);
		void onEraseBackground(wxEraseEvent& event);
		void onMouse(wxMouseEvent& event);

	private:
		static const int DRAG_FLAG_SIZE = 3;
		static const int DRAG_FLAG_RADIUS = 4;

	private:
		LayersPanel* m_parent;
		LayersMgr* m_layersMgr;

		int m_dragFlagLine;

		DECLARE_EVENT_TABLE()

	}; // LayersContentWidget
}

#endif // _FRUITS_ANIMATOR_LAYERS_CONTENT_WIDGET_H_