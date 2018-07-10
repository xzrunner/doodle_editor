#ifndef _EASY_BUILDER_SCENE_H_
#define _EASY_BUILDER_SCENE_H_

#include <wxGUI/wxGUI.h>

namespace ebuilder
{
	class Actor;

	class Scene
	{
	public:
		Scene();
		virtual ~Scene();

		const std::vector<Actor*>& getActors() const {
			return m_actors;
		}

		void insertActor(Actor* actor);
		void removeActor(Actor* actor);

		void clear();

	public:
		wxString m_name;

		wxString m_tag;

		wxColor m_color;

	private:
		std::vector<Actor*> m_actors;

	}; // Scene
}

#endif // _EASY_BUILDER_SCENE_H_