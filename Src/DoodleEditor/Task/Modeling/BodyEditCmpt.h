#ifndef _DEDITOR_MODELING_BODY_EDIT_CMPT_H_
#define _DEDITOR_MODELING_BODY_EDIT_CMPT_H_

#include <wxGUI/wxGUI.h>

namespace deditor
{
	namespace modeling
	{
		class StagePanel;

		class BodyEditCmpt : public wxgui::AbstractEditCMPT
		{
		public:
			BodyEditCmpt(wxWindow* parent, const wxString& name,
				StagePanel* editPanel, wxgui::PropertySettingPanel* propertyPanel);

		protected:
			virtual wxSizer* initLayout();

		}; // BodyEditCmpt
	}
}

#endif // _DEDITOR_MODELING_BODY_EDIT_CMPT_H_