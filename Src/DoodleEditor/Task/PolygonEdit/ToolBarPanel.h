#ifndef _DEDITOR_POLYGON_EDIT_TOOLBAR_PANEL_H_
#define _DEDITOR_POLYGON_EDIT_TOOLBAR_PANEL_H_

#include <wxGUI/wxGUI.h>

namespace deditor
{
	namespace polygon_edit
	{
		class StagePanel;

		class ToolbarPanel : public wxgui::ToolbarPanel
		{
		public:
			ToolbarPanel(wxWindow* parent, StagePanel* editPanel);
			virtual ~ToolbarPanel();

			wxgui::LayersMgrWidget* getLayersMgr() { 
				return m_layersMgr; 
			}

		protected:
			virtual wxSizer* initLayout();

		private:
			StagePanel* m_editPanel;

			wxgui::LayersMgrWidget* m_layersMgr;

		}; // ToolbarPanel
	}
}

#endif // _DEDITOR_POLYGON_EDIT_TOOLBAR_PANEL_H_