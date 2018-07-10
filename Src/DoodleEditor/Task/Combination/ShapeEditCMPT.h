#ifndef _DEDITOR_COMBINATION_SHAPE_EDIT_CMPT_H_
#define _DEDITOR_COMBINATION_SHAPE_EDIT_CMPT_H_

#include <wxGUI/wxGUI.h>

namespace deditor
{
	namespace combination
	{
		class StagePanel;

		class ShapeEditCMPT : public wxgui::DrawPolylineCMPT
		{
		public:
			ShapeEditCMPT(wxWindow* parent, const wxString& name,
				StagePanel* editPanel);

// 			bool isBorderExtractState() const { return m_extractCheck->IsChecked(); }
// 
// 			wxgui::RawPixels* getPixelsData() { return m_pixelsData; }

		protected:
			virtual wxSizer* initLayout();

		private:
			StagePanel* m_editPanel;

// 			wxCheckBox* m_extractCheck;
// 
// 			wxgui::RawPixels* m_pixelsData;

		}; // ShapeEditCMPT
	}
}

#endif // _DEDITOR_COMBINATION_SHAPE_EDIT_CMPT_H_