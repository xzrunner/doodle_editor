#ifndef _GAME_FRUITS_VIEW_BACKSTAGE_SCENE_PAGE_H_
#define _GAME_FRUITS_VIEW_BACKSTAGE_SCENE_PAGE_H_
#include "DstPageBase.h"

class wxNotebook;

namespace GAME_FRUITS
{
	class Scene;

	namespace VIEW
	{
		namespace BACKSTAGE
		{
			class ScenePage : public DstPageBase
			{
			public:
				ScenePage(wxNotebook* parent, Scene* scene);

				void initData(Scene* scene);

			private:
				void buildPropertyPage();

				void buildNameItem(wxSizer* topSizer);
				void buildColorItem(wxSizer* topSizer);

				void setColorButtonColor();

				void onNameChange(wxCommandEvent& event);
				void onSetColor(wxCommandEvent& event);

			private:
				wxNotebook* m_parent;
				Scene* m_scene;

				wxTextCtrl* m_name;
				wxButton* m_setColor;

			}; // ScenePage
		}
	}
}

#endif // _GAME_FRUITS_FRAME_BACKSTAGE_SCENE_PAGE_H_