#ifndef _GAME_FRUITS_OUTPUT_CPLUSPLUS_PAGE_H_
#define _GAME_FRUITS_OUTPUT_CPLUSPLUS_PAGE_H_
#include "OutputPageBase.h"
#include <wx/wx.h>

class wxNotebook;
class wxStyledTextCtrl;

namespace GAME_FRUITS
{
	namespace OUTPUT
	{
		class CPlusPlusPage : public wxPanel, public OutputPageBase
		{
		public:
			CPlusPlusPage(wxWindow* parent);

			//
			// IScenePage interface
			//
			virtual void storeToInterimData(InterimData& interim) const;
			virtual void loadFromInterimData(const InterimData& interim);

		private:
			void initTabPages();

			// header
			wxString getHeaderCode(const InterimData& interim) const;
			// cpp
			wxString getCPPHeaderCode(const InterimData& interim) const;
			wxString getFuncSceneCode(const InterimData& interim) const;
			wxString getFuncInitCode(const InterimData& interim) const;
			wxString getFuncCallbackCode(const InterimData& interim) const;

		private:
			wxNotebook* m_notebook;

			wxStyledTextCtrl* m_hFile;
			wxStyledTextCtrl* m_cppFile;

		}; // CPlusPlusPage
	}
}

#endif // _GAME_FRUITS_OUTPUT_CPLUSPLUS_PAGE_H_