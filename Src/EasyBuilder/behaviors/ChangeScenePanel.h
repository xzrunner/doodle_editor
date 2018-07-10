#ifndef _EASY_BUILDER_CHANGE_SCENE_PANEL_H_
#define _EASY_BUILDER_CHANGE_SCENE_PANEL_H_

#include "BehaviorPanel.h"

namespace ebuilder
{
	class ChangeScene;

	class ChangeScenePanel : public BehaviorPanel
	{
	public:
		virtual void update(const wxgui::LibraryList& list);

	private:
		ChangeScenePanel(wxWindow* parent, wxgui::LibraryList* sceneList,
			ChangeScene* behavior);

	protected:
		virtual wxSizer* createExtend(wxWindow* extend);

	private:
		wxSizer* createChooseListItem(wxWindow* extend);

		void onChoiceChanged(wxCommandEvent& event);

		void initChoice();

	private:
		wxgui::LibraryList* m_list;

		ChangeScene* m_behavior;

		wxChoice* m_choice;

		friend class BehaviorFactory;

	}; // ChangeScenePanel
}

#endif // _EASY_BUILDER_CHANGE_SCENE_PANEL_H_
