#ifndef _EASY_BUILDER_CHANGE_SCENE_H_
#define _EASY_BUILDER_CHANGE_SCENE_H_

#include "Behavior.h"

namespace ebuilder
{
	class ScenesPage;

	class ChangeScene : public Behavior
	{
	public:
		virtual ~ChangeScene();

		virtual void update(const wxgui::LibraryList& list);

		void registerListener(ScenesPage* scenePage);

	private:
		ChangeScene(Actor* actor, wxgui::LibraryList* sceneList);

	public:
		wxgui::ISymbol* selected;

		ScenesPage* m_scenePage;

		friend class BehaviorFactory;

	}; // ChangeScene
}

#endif // _EASY_BUILDER_CHANGE_SCENE_H_