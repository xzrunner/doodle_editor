#ifndef _DEDITOR_BASE_TASK_H_
#define _DEDITOR_BASE_TASK_H_

#include <wxGUI/wxGUI.h>
#include <wx/splitter.h>

namespace deditor
{
	class BaseTask
	{
	public:
		virtual ~BaseTask();

		virtual void loadFromTextFile(const char* filename) = 0;
		virtual void storeToTextFile(const char* filename) const = 0;

		virtual const wxString& getFileTag() const = 0;
		virtual void clear() = 0;

		virtual void onPreview() const {}

		wxgui::GLCanvas* getCanvas() const;

	protected:
		BaseTask(wxFrame* parent);

 		virtual void initWindows(wxSplitterWindow* leftHorizontalSplitter, 
			wxSplitterWindow* leftVerticalSplitter, wxSplitterWindow* rightVerticalSplitter,
 			wxWindow*& library, wxWindow*& property, wxWindow*& stage, wxWindow*& toolbar) = 0;

		void initLayout();

	protected:
		wxWindow* m_root;

		wxFrame* m_parent;

		wxWindow* m_stageView;

	}; // BaseTask
}

#endif // _DEDITOR_BASE_TASK_H_