#ifndef _GAME_FRUITS_VIEW_LIBRARY_SCENE_PAGE_H_
#define _GAME_FRUITS_VIEW_LIBRARY_SCENE_PAGE_H_
#include "LibraryPageBase.h"

class wxListEvent;

namespace GAME_FRUITS
{
	class Scene;

	namespace VIEW
	{
		namespace LIBRARY
		{
			class ScenePage : public LibraryPageBase
			{
			public:
				ScenePage(wxWindow* parent);

				void setName(const wxString& from, const wxString& to);

				void updateThumbnail(const Scene& scene);

			private:
				void initLayout();

				void onAddScene(wxCommandEvent& event);
				void onDelScene(wxCommandEvent& event);

				void onListItemSelected(wxListEvent& event);

				void add(Scene* scene);

				int queryImageID(const wxString& item);

			private:
				static const int IMG_WIDTH = 80;
				static const int IMG_HEIGHT = 48;

			private:
				wxImageList* m_imageList;

			}; // ScenePage
		}
	}
}

#endif // _GAME_FRUITS_VIEW_LIBRARY_SCENE_PAGE_H_