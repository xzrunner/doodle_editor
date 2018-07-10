#ifndef _GAME_FRUITS_VIEW_BACKSTAGE_PERSISTENT_PAGE_H_
#define _GAME_FRUITS_VIEW_BACKSTAGE_PERSISTENT_PAGE_H_
#include "SrcPageBase.h"

namespace GAME_FRUITS
{
	namespace VIEW
	{
		namespace BACKSTAGE
		{
			class SrcPanel;

			class PersistentPage : public SrcPageBase
			{
			public:
				PersistentPage(SrcPanel* parent);

			protected:
				virtual void initFunctions();

			private:
				void onDragInit(wxListEvent& event);

			}; // PersistentPage
		}
	}
}

#endif // _GAME_FRUITS_VIEW_BACKSTAGE_PERSISTENT_PAGE_H_