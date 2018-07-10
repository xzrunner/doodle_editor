#ifndef _EASY_BUILDER_CODE_PAGE_H_
#define _EASY_BUILDER_CODE_PAGE_H_

#include <wx/stc/stc.h>

struct LanguageInfo;

namespace ebuilder
{
	class CodePage : public wxStyledTextCtrl
	{
	public:
		CodePage(wxWindow* parent, const wxString& name);
		virtual ~CodePage() {}

		const wxString& getName() const;

	protected:
		//! language/lexer
		wxString DeterminePrefs (const wxString &filename);
		bool InitializePrefs (const wxString &filename);

	private:
		wxString m_name;

		// lanugage properties
		const LanguageInfo* m_language;

		// margin variables
		int m_LineNrID;
		int m_LineNrMargin;
		int m_FoldingID;
		int m_FoldingMargin;
		int m_DividerID;

	}; // CodePage
}

#endif // _EASY_BUILDER_CODE_PAGE_H_