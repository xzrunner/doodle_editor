#ifndef _EASY_BUILDER_CODE_PAGE_BUILDER_H_
#define _EASY_BUILDER_CODE_PAGE_BUILDER_H_

#include "CodePage.h"

#include <wx/wx.h>
#include <wx/notebook.h>

namespace ebuilder
{
	class SceneItem;

	class CodePageBuilder
	{
	public:
		CodePageBuilder(wxNotebook* notebook);
		virtual ~CodePageBuilder() {}

		virtual void loadPages() = 0;

		virtual void updatePage(const SceneItem& scene) = 0;

		virtual void insertPage(const SceneItem& scene) = 0;

		virtual void removePage(const SceneItem& scene) = 0;

	protected:
		void addPage(CodePage* page);

	protected:
		static int getSceneIndex(const SceneItem& scene);

	protected:
		wxNotebook* m_notebook;

	}; // CodePageBuilder
}

#endif // _EASY_BUILDER_CODE_PAGE_BUILDER_H_