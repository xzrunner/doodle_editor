#ifndef _EASY_BUILDER_ACTOR_ITEM_H_
#define _EASY_BUILDER_ACTOR_ITEM_H_

#include <wxGUI/wxGUI.h>

namespace ebuilder
{
	class Actor;

	class ActorItem : public wxgui::ISymbol
	{
	public:
		ActorItem(Actor* actor);
		virtual ~ActorItem() {}

		//
		// IObject interface
		//	
		virtual ActorItem* clone() { return NULL; }

		//
		// ISerializable interface
		//
		virtual void loadFromTextFile(std::ifstream& fin);
		virtual void storeToTextFile(std::ofstream& fout) const;

		//
		// wxgui::ISymbol interface
		//
		virtual void reloadTexture() const;
		virtual void draw() const;
		virtual float getWidth() const;
		virtual float getHeight() const;

		Actor* getActor() const {
			return m_actor;
		}

	protected:
		virtual void loadResources();

	private:
		Actor* m_actor;

	}; // ActorItem
}

#endif // _EASY_BUILDER_ACTOR_ITEM_H_