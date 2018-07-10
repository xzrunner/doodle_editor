#ifndef _DEDITOR_COMBINATION_ARRANGE_SPRITE_CMPT_H_
#define _DEDITOR_COMBINATION_ARRANGE_SPRITE_CMPT_H_

#include <wxGUI/wxGUI.h>

namespace deditor
{
	namespace combination
	{
		class StagePanel;

		class ArrangeSpriteCMPT : public wxgui::AbstractEditCMPT
		{
		public:
			ArrangeSpriteCMPT(wxWindow* parent, const wxString& name,
				StagePanel* editPanel, wxgui::PropertySettingPanel* propertyPanel);
		
		protected:
			virtual wxSizer* initLayout();

		private:
			void onHorizontalFlip(wxCommandEvent& event);
			void onVerticalFlip(wxCommandEvent& event);

		}; // ArrangeSpriteCMPT
	}
}

#endif // _DEDITOR_COMBINATION_ARRANGE_SPRITE_CMPT_H_