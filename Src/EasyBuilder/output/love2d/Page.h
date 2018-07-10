#ifndef _EASY_BUILDER_LOVE2D_PAGE_H_
#define _EASY_BUILDER_LOVE2D_PAGE_H_

#include "../CodePage.h"

namespace ebuilder
{
namespace love2d
{
	class Page : public CodePage
	{
	public:
		Page(wxWindow* parent, const wxString& name)
			: CodePage(parent, name) {
				InitializePrefs ("Lua");
		}

	}; // Page
}
}

#endif // _EASY_BUILDER_LOVE2D_PAGE_H_