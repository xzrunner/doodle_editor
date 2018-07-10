#ifndef _GAME_FRUITS_VIEW_LIBRARY_SPRITES_PAGE_H_
#define _GAME_FRUITS_VIEW_LIBRARY_SPRITES_PAGE_H_
#include "LibraryPageBase.h"

namespace GAME_FRUITS
{
	namespace VIEW
	{
		namespace LIBRARY
		{
			class SpritesPage : public LibraryPageBase
			{
			public:
				SpritesPage(wxWindow* parent);

			private:
				void initLayout();

				void onAddSprite(wxCommandEvent& event);
				void onDelSprite(wxCommandEvent& event);

			}; // SpritesPage
		}
	}
}

#endif // _GAME_FRUITS_VIEW_LIBRARY_SPRITES_PAGE_H_