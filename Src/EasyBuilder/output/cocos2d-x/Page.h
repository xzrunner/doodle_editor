#ifndef _EASY_BUILDER_CC_PAGE_H_
#define _EASY_BUILDER_CC_PAGE_H_

#include "../CodePage.h"

namespace ebuilder
{
	namespace cc
	{
		class Page : public CodePage
		{
		public:
			Page(wxWindow* parent, const wxString& name)
				: CodePage(parent, name) {
					InitializePrefs ("C++");
			}

		}; // Page
	}
}

#endif // _EASY_BUILDER_CC_PAGE_H_