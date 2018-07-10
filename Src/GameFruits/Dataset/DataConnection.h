#ifndef _GAME_FRUITS_DATA_CONNECTION_H_
#define _GAME_FRUITS_DATA_CONNECTION_H_
#include "Dataset/Game.h"

class wxNotebook;

namespace GAME_FRUITS
{
	class Object;

	namespace VIEW
	{
		namespace BACKSTAGE
		{
			class DstPanel;
		}
	}

	class DataConnection
	{
	public:

		static Game m_game;

		static Scene* m_currScene;

		static Object* m_currObject;

		static wxWindow* m_stage;

		static VIEW::BACKSTAGE::DstPanel* m_dstPanel;

		static wxNotebook* m_libraryNotebook;

	}; // DataConnection
}

#endif // _GAME_FRUITS_DATA_CONNECTION_H_