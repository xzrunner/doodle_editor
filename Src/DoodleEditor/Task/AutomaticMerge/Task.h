#ifndef _DEDITOR_AUTOMATIC_MERGE_TASK_H_
#define _DEDITOR_AUTOMATIC_MERGE_TASK_H_

#include "Frame/BaseTask.h"

#include <wxGUI/wxGUI.h>

namespace deditor
{
	namespace automatic_merge
	{
		class StagePanel;
		class ToolbarPanel;

		class Task : public BaseTask
		{
		public:

			virtual void loadFromTextFile(const char* filename);
			virtual void storeToTextFile(const char* filename) const;

			virtual const wxString& getFileTag() const;
			virtual void clear();

			static BaseTask* create(wxFrame* parent)
			{
				return new Task(parent);
			}

		protected:
			Task(wxFrame* parent);

			virtual void initWindows(wxSplitterWindow* leftHorizontalSplitter, 
				wxSplitterWindow* leftVerticalSplitter, wxSplitterWindow* rightVerticalSplitter,
				wxWindow*& library, wxWindow*& property, wxWindow*& stage, wxWindow*& toolbar);

		private:
			wxgui::LibraryPanel* m_libraryPanel;

			wxgui::PropertySettingPanel* m_propertyPanel;

			StagePanel* m_stage;

			ToolbarPanel* m_toolbar;

		}; // Task
	}
}

#endif // _DEDITOR_AUTOMATIC_MERGE_TASK_H_