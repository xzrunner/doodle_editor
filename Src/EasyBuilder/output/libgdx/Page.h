#ifndef _EASY_BUILDER_LIBGDX_PAGE_H_
#define _EASY_BUILDER_LIBGDX_PAGE_H_

#include "../CodePage.h"

namespace ebuilder
{
	namespace libgdx
	{
		class Page : public CodePage
		{
		public:
			Page(wxWindow* parent, const wxString& name)
				: CodePage(parent, name) {
					InitializePrefs("Java");
			}

		}; // Page
	}
}

#endif // _EASY_BUILDER_LIBGDX_PAGE_H_