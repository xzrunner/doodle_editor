#ifndef _GAME_FRUITS_REGULAR_CHANGE_SCENE_H_
#define _GAME_FRUITS_REGULAR_CHANGE_SCENE_H_
#include "RegularListItem.h"

namespace GAME_FRUITS
{
	class Scene;

	namespace REGULAR
	{
		class ChangeScene : public RegularListItem
		{
		public:
			ChangeScene();

			Scene* getSelectedScene() const;

		protected:
			virtual wxSizer* createExtend(wxWindow* extend);

		private:
			wxSizer* createChooseListItem(wxWindow* extend);

		private:
			wxChoice* m_selectList;

		}; // ChangeScene
	}
}

#endif // _GAME_FRUITS_REGULAR_CHANGE_SCENE_H_