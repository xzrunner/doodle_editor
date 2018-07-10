#ifndef _WX_GUI_UNIVERSAL_CMPT_H_
#define _WX_GUI_UNIVERSAL_CMPT_H_

#include "AbstractEditCMPT.h"

namespace wxgui
{
	class UniversalCMPT : public AbstractEditCMPT
	{
	public:
		UniversalCMPT(wxWindow* parent, const wxString& name,
			EditPanel* editPanel, AbstractEditOP* editOP);

	protected:
		virtual wxSizer* initLayout();

	}; // UniversalCMPT
}

#endif // _WX_GUI_UNIVERSAL_CMPT_H_