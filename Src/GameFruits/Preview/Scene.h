#ifndef _GAME_FRUITS_PREVIEW_SCENE_H_
#define _GAME_FRUITS_PREVIEW_SCENE_H_
#include <Fruits2D/Fruits2D.h>
#include <wx/wx.h>

namespace GAME_FRUITS
{
	class Object;
	class Scene;

	namespace REGULAR
	{
		class MousePress;
	}

	namespace PREVIEW
	{
		class MainDialog;
		class Sprite;
		class Button;

		class Scene
		{
		public:
			Scene(MainDialog* main, GAME_FRUITS::Scene* src);
			~Scene();

			void onPaint(wxDC& dc) const;

			void onMouseDown(int x, int y);
			void onMouseUp(int x, int y);

		private:
			void loadFromEditor(GAME_FRUITS::Scene* src);

			void loadObject(GAME_FRUITS::Object* obj);

			void loadTileObject(GAME_FRUITS::Object* obj);
			void loadButtonObject(GAME_FRUITS::Object* obj);
			void loadButtonObject(Button* button, GAME_FRUITS::REGULAR::MousePress* press);

		private:
			MainDialog* m_main;

			wxColour m_bgColor;

			std::vector<Sprite*> m_tiles;
			std::vector<Button*> m_buttons;

		}; // Scene
	}
}

#endif // _GAME_FRUITS_PREVIEW_SCENE_H_