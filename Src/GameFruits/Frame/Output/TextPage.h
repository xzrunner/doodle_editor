#ifndef _GAME_FRUITS_OUTPUT_TEXT_PAGE_H_
#define _GAME_FRUITS_OUTPUT_TEXT_PAGE_H_
#include "OutputPageBase.h"
#include <wx/wx.h>
#include <wx/stc/stc.h>

namespace GAME_FRUITS
{
	namespace OUTPUT
	{
		class TextPage : public wxStyledTextCtrl, public OutputPageBase
		{
		public:
			TextPage(wxWindow* parent);

			//
			// IScenePage interface
			//
			virtual void storeToInterimData(InterimData& interim) const;
			virtual void loadFromInterimData(const InterimData& interim);

		}; // TextPage
	}
}

#endif // _GAME_FRUITS_OUTPUT_TEXT_PAGE_H_