#ifndef _FRUITS_ANIMATOR_TIME_LINE_PANEL_H_
#define _FRUITS_ANIMATOR_TIME_LINE_PANEL_H_

#include "Fruits2D/Fruits2D.h"
#include <wx/wx.h>

namespace FRUITS_ANIMATOR
{
	class Layer;
	class LayersMgr;
	class LayersPanel;
	class LibraryPanel;
	class KeysPanel;
	class StagePanel;

	class TimeLinePanel : public wxPanel
	{
	public:
		TimeLinePanel(wxWindow* parent);
		virtual ~TimeLinePanel();

		void loadFromTextFile(std::ifstream& fin, const LibraryPanel& library);
		void storeToTextFile(std::ofstream& fout, const LibraryPanel& library) const;

		LayersMgr* getLayerMgr() const;
		Layer* getCurrLayer() const;
		int getCurrFrame() const;

		void setStagePanel(StagePanel* stagePanel);

		int getFPSVal() const; 

		// bad
		LayersPanel* getLayersPanel();
		KeysPanel* getKeysPanel();

		void clear();

	private:
		void initLayout();

		void initTitle(wxSizer* sizer);
		void initSplitterWindow(wxSizer* sizer);

	private:
		static const float SASH_GRAVITY_VERT;

	private:
		LayersMgr* m_layersMgr;

		LayersPanel* m_layersPanel;
		KeysPanel* m_keysPanel;

	}; // TimeLinePanel
}

#endif // _FRUITS_ANIMATOR_TIME_LINE_PANEL_H_