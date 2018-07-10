#ifndef _EASY_BUILDER_STAGE_PANEL_H_
#define _EASY_BUILDER_STAGE_PANEL_H_

#include <wxGUI/wxGUI.h>
#include <wx/wx.h>
#include <wx/notebook.h>

namespace ebuilder
{
	class DesignerPage;
	class SceneItem;
	class CodePageBuilder;

	class StagePanel : public wxPanel
	{
	public:
		StagePanel(wxWindow* parent);

		DesignerPage* getDesignerPage() const {
			return m_designerPage;
		}

		void rebuildCodePages();
		void updateCodePages(SceneItem* scene) const;
		void addCodePage(SceneItem* scene);
		void removeCodePage(SceneItem* scene);

		void storeAllCodePages(const wxString& dir) const;

		void clear();

	private:
		void initLayout();

		void initTitle(wxSizer* sizer);
		void initTabPages(wxSizer* sizer);

		void onPageChanged(wxNotebookEvent& event);

		CodePageBuilder* getCodePageBuilder() const;

	private:
		wxNotebook* m_notebook;

		DesignerPage* m_designerPage;

		DECLARE_EVENT_TABLE()

	}; // StagePanel
}

#endif // _EASY_BUILDER_STAGE_PANEL_H_