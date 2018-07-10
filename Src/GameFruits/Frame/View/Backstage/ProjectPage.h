#ifndef _GAME_FRUITS_VIEW_BACKSTAGE_PROJECT_PAGE_H_
#define _GAME_FRUITS_VIEW_BACKSTAGE_PROJECT_PAGE_H_
#include "DstPageBase.h"

class wxNotebook;

namespace GAME_FRUITS
{
	namespace VIEW
	{
		namespace BACKSTAGE
		{
			class ProjectPage : public DstPageBase
			{
			public:
				ProjectPage(wxNotebook* parent);

			private:
				void buildPropertyPage();

				void buildNameItem(wxSizer* topSizer);
				void buildSizeItem(wxSizer* topSizer);

			private:
				void onNameChange(wxCommandEvent& event);

			private:
				wxNotebook* m_parent;

			}; // ProjectPage
		}
	}
}

#endif // _GAME_FRUITS_FRAME_BACKSTAGE_PROJECT_PAGE_H_