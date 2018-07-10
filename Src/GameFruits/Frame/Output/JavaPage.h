#ifndef _GAME_FRUITS_OUTPUT_JAVA_PAGE_H_
#define _GAME_FRUITS_OUTPUT_JAVA_PAGE_H_
#include "OutputPageBase.h"
#include <wx/wx.h>
#include <wx/stc/stc.h>

namespace GAME_FRUITS
{
	namespace OUTPUT
	{
		class JavaPage : public wxStyledTextCtrl, public OutputPageBase
		{
		public:
			JavaPage(wxWindow* parent);

			//
			// IScenePage interface
			//
			virtual void storeToInterimData(InterimData& interim) const;
			virtual void loadFromInterimData(const InterimData& interim);

		}; // JavaPage
	}
}

#endif // _GAME_FRUITS_OUTPUT_JAVA_PAGE_H_