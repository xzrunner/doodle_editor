#ifndef _GAME_FRUITS_VIEW_LIBRARY_SOUNDS_PAGE_H_
#define _GAME_FRUITS_VIEW_LIBRARY_SOUNDS_PAGE_H_
#include "LibraryPageBase.h"

namespace GAME_FRUITS
{
	namespace VIEW
	{
		namespace LIBRARY
		{
			class SoundsPage : public LibraryPageBase
			{
			public:
				SoundsPage(wxWindow* parent);

			private:
				void initLayout();

				void onAddSound(wxCommandEvent& event);
				void onDelSound(wxCommandEvent& event);

			}; // SoundsPage
		}
	}
}

#endif // _GAME_FRUITS_VIEW_LIBRARY_SOUNDS_PAGE_H_