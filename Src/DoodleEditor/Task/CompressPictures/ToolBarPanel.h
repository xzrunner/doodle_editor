#ifndef _DEDITOR_COMPRESS_PICTURE_TOOLBAR_PANEL_H_
#define _DEDITOR_COMPRESS_PICTURE_TOOLBAR_PANEL_H_

#include <wxGUI/wxGUI.h>

namespace deditor
{
	namespace compress_pictures
	{
		class LibrarySymbolList;
		struct CompressParams;

		class ToolbarPanel : public wxgui::ToolbarPanel
		{
		public:
			ToolbarPanel(wxWindow* parent, wxgui::EditPanel* editPanel);

			void changeSymbol(const wxgui::ISymbol* symbol);

			void setLibraryList(LibrarySymbolList* libraryList);

			void updateParamsPanel(const wxString& src, const wxString& dst);

			void getCompressParams(CompressParams& params) const;

		protected:
			virtual wxSizer* initLayout();

		private:
			void initJpgPanel(wxSizer* topSizer);
			void initPngPanel(wxSizer* topSizer);
			void initParamsPanel(wxSizer* topSizer);
			void initBatchPanel(wxSizer* topSizer);

			void onChangeSettings(wxCommandEvent& event);
			void onChangeSettings(wxScrollEvent& event);
			void onBatchBtnPress(wxCommandEvent& event);

		private:
			LibrarySymbolList* m_libraryList;

			wxSizer* m_jpgSizer;
			wxSizer* m_pngSizer;
			wxSizer* m_paramsSizer;

			wxSlider* m_jpgSlider;
			wxChoice *m_pngColorChoice, *m_pngSpeedChoice;
			
			wxTextCtrl *m_srcSizeText, *m_dstSizeText, *m_compressRatio;

		}; // ToolbarPanel
	}
}

#endif // _DEDITOR_COMPRESS_PICTURE_TOOLBAR_PANEL_H_