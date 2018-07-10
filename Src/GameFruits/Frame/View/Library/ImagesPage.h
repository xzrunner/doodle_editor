#ifndef _GAME_FRUITS_VIEW_LIBRARY_IMAGES_PAGE_H_
#define _GAME_FRUITS_VIEW_LIBRARY_IMAGES_PAGE_H_
#include "LibraryPageBase.h"

class wxListEvent;

namespace GAME_FRUITS
{
	namespace VIEW
	{
		namespace LIBRARY
		{
			class ImagesPage : public LibraryPageBase
			{
			public:
				ImagesPage(wxWindow* parent);

				wxString getImagePath(const wxString& imgName) const;

			private:
				void onAddImage(wxCommandEvent& event);
				void onDelImage(wxCommandEvent& event);

				void onDragInit(wxListEvent& event);

			private:
				static const int IMG_LIST_GRID_EDGE = 64;

			private:
				wxImageList* m_imageList;

			}; // ImagesPage
		}
	}
}

#endif // _GAME_FRUITS_VIEW_LIBRARY_IMAGES_PAGE_H_