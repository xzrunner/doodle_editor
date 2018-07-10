#ifndef _EASY_BUILDER_CHANGE_IMAGE_PANEL_H_
#define _EASY_BUILDER_CHANGE_IMAGE_PANEL_H_

#include "BehaviorPanel.h"

namespace ebuilder
{
	class ChangeImage;

	class ChangeImagePanel : public BehaviorPanel
	{
	public:
		virtual void update(const wxgui::LibraryList& list);

	private:
		ChangeImagePanel(wxWindow* parent, wxgui::LibraryList* mediaList, 
			ChangeImage* behavior);

	protected:
		virtual wxSizer* createExtend(wxWindow* extend);

	private:
		wxSizer* createChooseListItem(wxWindow* extend);

		void onChoiceChanged(wxCommandEvent& event);

		void initChoice();

	private:
		wxgui::LibraryList* m_list;

		ChangeImage* m_behavior;

		wxChoice* m_choice;

		friend class BehaviorFactory;

	}; // ChangeImagePanel
}

#endif // _EASY_BUILDER_CHANGE_IMAGE_PANEL_H_