#ifndef _D2D_GAME_H_
#define _D2D_GAME_H_

namespace d2d
{
	class Scene;

	class Game
	{
	public:
		Game();

		void setScene(Scene* scene);
		Scene* getScene();

		void load();
		void draw() const;
		void update();

		bool isAlive() const;

	private:
		Scene* m_scene;

	}; // Game
}

#endif // _D2D_GAME_H_