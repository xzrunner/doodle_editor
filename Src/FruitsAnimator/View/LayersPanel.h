#ifndef _FRUITS_ANIMATOR_LAYERS_PANEL_H_
#define _FRUITS_ANIMATOR_LAYERS_PANEL_H_
#include <wx/wx.h>

namespace FRUITS_ANIMATOR
{
	class TimeLinePanel;
	class LayersMgr;
	class LayersPropertyWidget;
	class LayersContentWidget;
	class StagePanel;

	class LayersPanel : public wxPanel
	{
	public:
		LayersPanel(wxWindow* parent, TimeLinePanel* timeLinePanel, LayersMgr* layersMgr);

		void onAddLayer();
		void onDelLayer();
		void onPlay();

		void setSelectedLayer(int index);
		int getSelectedLayer() const;

		void setStagePanel(StagePanel* stagePanel);

		void refreshKeysPanel() const;

		int getFPSVal() const; 

	private:
		void initLayout();

	private:
		TimeLinePanel* m_timeLinePanel;
		LayersMgr* m_layersMgr;
		StagePanel* m_stagePanel;

		LayersPropertyWidget* m_propertyWidget;
		LayersContentWidget* m_contentWidget;

		int m_selected;

	}; // LayersPanel
}

#endif // _FRUITS_ANIMATOR_LAYERS_PANEL_H_