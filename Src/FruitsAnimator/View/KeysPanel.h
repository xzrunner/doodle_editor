#ifndef _FRUITS_ANIMATOR_KEYS_PANEL_H_
#define _FRUITS_ANIMATOR_KEYS_PANEL_H_
#include <wx/wx.h>

namespace FRUITS_ANIMATOR
{
	class TimeLinePanel;
	class StagePanel;
	class LayersMgr;
	class KeysScaleWidget;
	class KeysContentWidget;

	class KeysPanel : public wxPanel
	{
	public:
		KeysPanel(wxWindow* parent, TimeLinePanel* timeLinePanel, LayersMgr* layersMgr);

		int getCurrPos() const;
		void setCurrPos(int pos);

		void getSelectPos(int& row, int& col) const;
		void setSelectPos(int row, int col);

		void setStagePanel(StagePanel* stagePanel);

	private:
		void initLayout();

	private:
		TimeLinePanel* m_timeLinePanel;
		LayersMgr* m_layersMgr;
		StagePanel* m_stagePanel;

		KeysScaleWidget* m_scaleWidget;
		KeysContentWidget* m_contentWidget;

		int m_currPos;	// start from 1

		int m_selectRow, m_selectCol;

	}; // KeysPanel
}

#endif // _FRUITS_ANIMATOR_KEYS_PANEL_H_