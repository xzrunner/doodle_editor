#ifndef _DEDITOR_MANUAL_COMPOSE_STAGE_PANEL_H_
#define _DEDITOR_MANUAL_COMPOSE_STAGE_PANEL_H_

#include <wxGUI/wxGUI.h>

namespace deditor
{
	namespace manual_compose
	{
		class StagePanel : public wxgui::EditPanel, public wxgui::SpritesPanelImpl
		{
		public:
			StagePanel(wxWindow* parent, 
				wxgui::PropertySettingPanel* propertyPanel,
				wxgui::LibraryPanel* libraryPanel);
			virtual ~StagePanel();

			virtual void clear();

			wxgui::ISprite* getBackground();
			void setBackground(const wxString& filePath);

		private:
			wxgui::ISprite* m_background;

		}; // StagePanel
	}
}

#endif // _DEDITOR_MANUAL_COMPOSE_STAGE_PANEL_H_