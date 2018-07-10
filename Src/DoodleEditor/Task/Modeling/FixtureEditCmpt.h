#ifndef _DEDITOR_MODELING_FIXTURE_EDIT_CMPT_H_
#define _DEDITOR_MODELING_FIXTURE_EDIT_CMPT_H_

#include <wxGUI/wxGUI.h>

namespace deditor
{
	namespace modeling
	{
		class StagePanel;

		class FixtureEditCmpt : public wxgui::AbstractEditCMPT
		{
		public:
			FixtureEditCmpt(wxWindow* parent, const wxString& name,
				StagePanel* editPanel, wxgui::PropertySettingPanel* propertyPanel);

		protected:
			virtual wxSizer* initLayout();

		}; // FixtureEditCmpt
	}
}

#endif // _DEDITOR_MODELING_FIXTURE_EDIT_CMPT_H_