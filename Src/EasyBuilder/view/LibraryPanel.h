#ifndef _EASY_BUILDER_LIBRARY_PANEL_H_
#define _EASY_BUILDER_LIBRARY_PANEL_H_

#include <wxGUI/wxGUI.h>

namespace ebuilder
{
	class Actor;
	class ActorsPage;
	class ScenesPage;
	class MediaPage;
	class BehaviorsPage;

	class LibraryPanel : public wxgui::LibraryPanel
	{
	public:
		LibraryPanel(wxWindow* parent);

		void addActor(Actor* actor);

		void clearUIListeners();

		wxgui::LibraryList* getSceneList();
		wxgui::LibraryList* getActorList();
		wxgui::LibraryList* getMediaList();
		wxgui::LibraryList* getBehaviorList();

		ScenesPage* getScenePage() { return m_scenePage; }
		MediaPage* getMediaPage() { return m_mediaPage; }

	private:
		void initLayout();

	private:
		void initTitle(wxSizer* sizer);
		void initNotebook(wxSizer* sizer);
		void initTabPages(wxSizer* sizer);

	private:
		ScenesPage* m_scenePage;
		ActorsPage* m_actorPage;
		MediaPage* m_mediaPage;
		BehaviorsPage* m_behaviorPage;

	}; // LibraryPanel
}

#endif // _EASY_BUILDER_LIBRARY_PANEL_H_