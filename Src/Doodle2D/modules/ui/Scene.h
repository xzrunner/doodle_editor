#ifndef _D2D_SCENE_H_
#define _D2D_SCENE_H_

#include <Doodle2D/doodle2d.h>

namespace d2d
{
	class Item;
	class Button;
	class Vector;

	class Scene
	{
	public:
		Scene(Game* game, d2d::Context* pContext);
		virtual ~Scene();
	
		virtual void load() = 0;
		virtual void draw() const;
		virtual void update();

		void setParent(Scene* parent) { 
			m_parent = parent;
		}

	protected:
		GraphicsSprite* loadSprite(const std::string& filename) const;

	private:
		d2d::Vector transInputPosToWorld(const Vector& pos) const;

		Button* queryButtonByPos(const Vector& pos) const;

	protected:
		Game* m_game;

		d2d::Context* m_pContext;

		Scene* m_parent;

		std::vector<Item*> m_backgrounds;
		std::vector<Item*> m_foregrounds;

	}; // Scene
}

#endif // _D2D_SCENE_H_