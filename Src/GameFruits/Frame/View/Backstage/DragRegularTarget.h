#ifndef _GAME_FRUITS_VIEW_BACKSTAGE_DRAG_REGULAR_TARGET_H_
#define _GAME_FRUITS_VIEW_BACKSTAGE_DRAG_REGULAR_TARGET_H_
#include <wx/dnd.h>

namespace GAME_FRUITS
{
	class RegularListItem;

	namespace VIEW
	{
		namespace BACKSTAGE
		{
			class DragRegularTarget : public wxTextDropTarget
			{
			public:
				DragRegularTarget(wxWindow* parent);

				virtual bool OnDropText(wxCoord x, wxCoord y, const wxString& data) = 0;

			protected:
				RegularListItem* createRegular(const wxString& name);

			protected:
				wxWindow* m_parent;

			}; // DragRegularTarget 
		}
	}
}

#endif // _GAME_FRUITS_VIEW_BACKSTAGE_DRAG_REGULAR_TARGET_H_