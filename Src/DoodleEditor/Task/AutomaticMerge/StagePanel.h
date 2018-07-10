#ifndef _DEDITOR_AUTOMATIC_MERGE_STAGE_PANEL_H_
#define _DEDITOR_AUTOMATIC_MERGE_STAGE_PANEL_H_

#include <wxGUI/wxGUI.h>

namespace deditor
{
	namespace automatic_merge
	{
		class BaseStrategy;

		class StagePanel : public wxgui::EditPanel, public wxgui::SpritesPanelImpl
		{
		public:
			StagePanel(wxWindow* parent, wxgui::PropertySettingPanel* propertyPanel,
				wxgui::LibraryPanel* libraryPanel);

			//
			// wxgui::SpritesPanelImpl interface
			//
			virtual void removeSprite(wxgui::ISprite* sprite);
			virtual void insertSprite(wxgui::ISprite* sprite);

			virtual void clear();

			void setOutputImageSize(int width, int height);
			void arrangeAllSprites(bool bClearSelection);
			void loadLibraryList();

			int getWidth() const { return m_width; }
			int getHeight() const { return m_height; }

		private:
			BaseStrategy* m_strategy;

			int m_width, m_height;

		}; // StagePanel
	}
}

#endif // _DEDITOR_AUTOMATIC_MERGE_STAGE_PANEL_H_