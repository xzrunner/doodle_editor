#ifndef _EASY_BUILDER_SCENE_ITEM_H_
#define _EASY_BUILDER_SCENE_ITEM_H_

#include <wxGUI/wxGUI.h>

namespace ebuilder
{
	class Actor;
	class Scene;

	class SceneItem : public wxgui::ISymbol
	{
	public:
		SceneItem(Scene* scene);
		virtual ~SceneItem();

		//
		// IObject interface
		//	
		virtual SceneItem* clone();

		//
		// ISerializable interface
		//
		virtual void loadFromTextFile(std::ifstream& fin);
		virtual void storeToTextFile(std::ofstream& fout) const;

		//
		// ISymbol interface
		//
		virtual void reloadTexture() const;
		virtual void draw() const;
		virtual float getWidth() const;
		virtual float getHeight() const;

		void insertActor(Actor* actor);
		void removeActor(Actor* actor);

		Scene* getScene() const {
			return m_scene;
		}

		const wxString& getName() const;
		void setName(const wxString& name);

		void refreshThumbnail();

	protected:
		virtual void loadResources() {}

	private:
		static const float THUMBNAIL_SCALE;

	private:
		Scene* m_scene;

	}; // SceneItem
}

#endif // _EASY_BUILDER_SCENE_ITEM_H_