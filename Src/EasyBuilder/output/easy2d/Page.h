#ifndef _EASY_BUILDER_E2D_PAGE_H_
#define _EASY_BUILDER_E2D_PAGE_H_

#include "../CodePage.h"

namespace ebuilder
{
	namespace e2d
	{
		class Page : public CodePage
		{
		public:
			Page(wxWindow* parent, const wxString& name)
				: CodePage(parent, name) {
				InitializePrefs ("C++"/*DEFAULT_LANGUAGE*/);
			}

		}; // Page
	}
}

#endif // _EASY_BUILDER_E2D_PAGE_H_