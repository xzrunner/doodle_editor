#ifndef _GAME_FRUITS_VIEW_BACKSTAGE_ACTION_PAGE_H_
#define _GAME_FRUITS_VIEW_BACKSTAGE_ACTION_PAGE_H_
#include "SrcPageBase.h"

namespace GAME_FRUITS
{
	namespace VIEW
	{
		namespace BACKSTAGE
		{
			class SrcPanel;

			class ActionPage : public SrcPageBase
			{
			public:
				ActionPage(SrcPanel* parent);

			protected:
				virtual void initFunctions();

			private:
				void onDragInit(wxListEvent& event);

			}; // ActionPage
		}
	}
}

#endif // _GAME_FRUITS_VIEW_BACKSTAGE_ACTION_PAGE_H_