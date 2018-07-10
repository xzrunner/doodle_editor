#ifndef _GAME_FRUITS_VIEW_BACKSTAGE_DST_PANEL_H_
#define _GAME_FRUITS_VIEW_BACKSTAGE_DST_PANEL_H_
#include <wx/wx.h>
#include <wx/notebook.h>

namespace GAME_FRUITS
{
	class Object;
	class Scene;

	namespace VIEW
	{
		namespace BACKSTAGE
		{
			class ScenePage;
			class ObjectPage;

			class DstPanel : public wxNotebook
			{
			public:
				DstPanel(wxWindow* parent);

				void setScenePage(Scene* scene);
				void setObjectPage(Object* object);

			}; // DstPanel
		}
	}
}

#endif // _GAME_FRUITS_VIEW_BACKSTAGE_DST_PANEL_H_