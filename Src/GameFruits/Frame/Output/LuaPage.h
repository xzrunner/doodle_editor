#ifndef _GAME_FRUITS_OUTPUT_LUA_PAGE_H_
#define _GAME_FRUITS_OUTPUT_LUA_PAGE_H_
#include "OutputPageBase.h"
#include <wx/wx.h>
#include <wx/stc/stc.h>

namespace GAME_FRUITS
{
	namespace OUTPUT
	{
		class LuaPage : public wxStyledTextCtrl, public OutputPageBase
		{
		public:
			LuaPage(wxWindow* parent);

			//
			// IScenePage interface
			//
			virtual void storeToInterimData(InterimData& interim) const;
			virtual void loadFromInterimData(const InterimData& interim);

		private:
			wxString getMainFuncCode(const InterimData& interim) const;
			wxString getCreateSceneFuncCode(const InterimData& interim) const;

		}; // LuaPage
	}
}

#endif // _GAME_FRUITS_OUTPUT_LUA_PAGE_H_