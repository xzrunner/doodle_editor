#ifndef _GAME_FRUITS_OUTPUT_XRC_PAGE_H_
#define _GAME_FRUITS_OUTPUT_XRC_PAGE_H_
#include "OutputPageBase.h"
#include <wx/wx.h>
#include <wx/stc/stc.h>

namespace GAME_FRUITS
{
	namespace OUTPUT
	{
		class XRCPage : public wxStyledTextCtrl, public OutputPageBase
		{
		public:
			XRCPage(wxWindow* parent);

			//
			// IScenePage interface
			//
			virtual void storeToInterimData(InterimData& interim) const;
			virtual void loadFromInterimData(const InterimData& interim);

		}; // XRCPage
	}
}

#endif // _GAME_FRUITS_OUTPUT_XRC_PAGE_H_