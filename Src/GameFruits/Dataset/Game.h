#ifndef _GAME_FRUITS_GAME_H_
#define _GAME_FRUITS_GAME_H_
#include <Fruits2D/Fruits2D.h>
#include <wx/wx.h>

namespace GAME_FRUITS
{
	class Scene;

	class Game
	{
	public:
		Game();
		~Game();

		Scene* queryScene(const wxString& name) const;
		void deleteScene(const wxString& name);

	public:
		std::vector<Scene*> m_scenes;

		wxString m_name;

		int m_width, m_height;

	}; // Game
}

#endif // _GAME_FRUITS_GAME_H_