#ifndef _DEDITOR_SHOOT_BUBBLE_TASK_H_
#define _DEDITOR_SHOOT_BUBBLE_TASK_H_

#include "Frame/BaseTask.h"

#include <wxGUI/wxGUI.h>

namespace deditor
{
	namespace shoot_bubble
	{
		class StagePanel;

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

			StagePanel* m_stage;

			wxgui::PropertySettingPanel* m_propertyPanel;

		}; // Task
	}
}

#endif // _DEDITOR_SHOOT_BUBBLE_TASK_H_