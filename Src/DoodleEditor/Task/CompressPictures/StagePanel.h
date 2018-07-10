#ifndef _DEDITOR_COMPRESS_PICTURE_STAGE_PANEL_H_
#define _DEDITOR_COMPRESS_PICTURE_STAGE_PANEL_H_

#include <wxGUI/wxGUI.h>

namespace deditor
{
	namespace compress_pictures
	{
		class ToolbarPanel;

		class StagePanel : public wxgui::EditPanel
		{
		public:
			StagePanel(wxWindow* parent);

			void setToolbar(ToolbarPanel* toolbar);
			void changeSymbol(wxgui::ISymbol* symbol);

			void compressSymbol();

		private:
			static const wxString TMP_FILE;

		private:
			ToolbarPanel* m_toolbar;

			wxgui::ISymbol* m_symbol;
			wxgui::ISymbol* m_compressedSymbol;

			friend class StageCanvas;

		}; // StagePanel
	}
}

#endif // _DEDITOR_COMPRESS_PICTURE_STAGE_PANEL_H_