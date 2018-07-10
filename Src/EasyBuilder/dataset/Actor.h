#ifndef _EASY_BUILDER_ACTOR_H_
#define _EASY_BUILDER_ACTOR_H_

#include <wxGUI/wxGUI.h>

namespace ebuilder
{
	class Behavior;

	class Actor : public wxgui::ImageSprite
	{
	public:
		Actor(wxgui::ImageSymbol* symbol);
		virtual ~Actor();

		//
		// IObject interface
		//
		virtual Actor* clone();

		const std::vector<Behavior*>& getBehaviors() const {
			return m_behaviors;
		}
		void addBehavior(Behavior* behavior) {
			m_behaviors.push_back(behavior);
		}
		void clearBehaviors();

	public:
		wxString m_name;

		wxString m_tag;

		bool m_isBg;

		int m_layer;

	private:
		std::vector<Behavior*> m_behaviors;

	}; // Actor
}

#endif // _EASY_BUILDER_ACTOR_H_