#ifndef _GAME_FRUITS_VIEW_LIBRARY_LAYERS_PAGE_H_
#define _GAME_FRUITS_VIEW_LIBRARY_LAYERS_PAGE_H_
#include "LibraryPageBase.h"

namespace GAME_FRUITS
{
	namespace VIEW
	{
		namespace LIBRARY
		{
			class LayersPage : public LibraryPageBase
			{
			public:
				LayersPage(wxWindow* parent);

			private:
				void initLayout();

				void onAddLayer(wxCommandEvent& event);
				void onDelLayer(wxCommandEvent& event);

			}; // LayersPage
		}
	}
}

#endif // _GAME_FRUITS_VIEW_LIBRARY_LAYERS_PAGE_H_