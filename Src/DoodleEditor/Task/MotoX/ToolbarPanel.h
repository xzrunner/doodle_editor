#ifndef _DEDITOR_MOTOX_TOOLBAR_PANEL_H_
#define _DEDITOR_MOTOX_TOOLBAR_PANEL_H_

#include <wxGUI/wxGUI.h>

namespace deditor
{
	namespace motox
	{
		class StagePanel;
		class LibraryCombinationList;
		class LibraryTemplateList;
		class TileEditCMPT;

		class ToolbarPanel : public wxgui::ToolbarPanel
		{
		public:
			ToolbarPanel(wxWindow* parent, wxgui::PropertySettingPanel* propertyPanel, 
				StagePanel* editPanel, wxgui::LibraryPanel* libraryPanel);

			wxgui::LayersMgrWidget* getLayersMgr();

		protected:
			virtual wxSizer* initLayout();

		private:
			TileEditCMPT* m_tileCMPT;

		}; // ToolbarPanel
	}
}

#endif // _DEDITOR_MOTOX_TOOLBAR_PANEL_H_