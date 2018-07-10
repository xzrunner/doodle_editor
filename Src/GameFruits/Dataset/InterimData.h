#ifndef _GAME_FRUITS_INTERIM_DATA_H_
#define _GAME_FRUITS_INTERIM_DATA_H_
#include <Fruits2D/Fruits2D.h>
#include <wx/wx.h>

namespace GAME_FRUITS
{
	class InterimData
	{
	public:
		struct Entry
		{
			wxString path;
			wxString name;
			int x, y;

		}; // Entry

		struct Button
		{
			Entry entry;
			wxString toSceneName;
		};

	public:
		std::string m_sceneName;

		std::vector<Entry> m_objects;
		std::vector<Button> m_buttons;

	}; // InterimData
}

#endif // _GAME_FRUITS_INTERIM_DATA_H_