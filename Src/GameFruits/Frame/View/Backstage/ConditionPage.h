#ifndef _GAME_FRUITS_VIEW_BACKSTAGE_CONDITION_PAGE_H_
#define _GAME_FRUITS_VIEW_BACKSTAGE_CONDITION_PAGE_H_
#include "SrcPageBase.h"

namespace GAME_FRUITS
{
	namespace VIEW
	{
		namespace BACKSTAGE
		{
			class SrcPanel;

			class ConditionPage : public SrcPageBase
			{
			public:
				ConditionPage(SrcPanel* parent);

			protected:
				virtual void initFunctions();

			private:
				void onDragInit(wxListEvent& event);

			}; // ConditionPage
		}
	}
}

#endif // _GAME_FRUITS_VIEW_BACKSTAGE_CONDITION_PAGE_H_