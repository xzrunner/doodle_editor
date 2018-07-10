#ifndef _GAME_FRUITS_VIEW_BACKSTAGE_OBJECT_PAGE_H_
#define _GAME_FRUITS_VIEW_BACKSTAGE_OBJECT_PAGE_H_
#include "DstPageBase.h"
#include "DragRegularTarget.h"

class wxNotebook;

namespace GAME_FRUITS
{
	class Object;

	namespace VIEW
	{
		namespace BACKSTAGE
		{
			class ObjectPage : public DstPageBase
			{
			public:
				ObjectPage(wxNotebook* parent, Object* object);

				void initData(Object* object, bool hasRegular);

			private:
				void buildPropertyPage();

				void buildNameItem(wxSizer* topSizer);
				void buildPositionItem(wxSizer* topSizer); 
				void buildSizeItem(wxSizer* topSizer);

				void onNameChange(wxCommandEvent& event);
				void onXChange(wxCommandEvent& event);
				void onYChange(wxCommandEvent& event);
				void onWidthChange(wxCommandEvent& event);
				void onHeightChange(wxCommandEvent& event);

			private:
				class DragTarget : public DragRegularTarget
				{
				public:
					DragTarget(wxWindow* parent, Object* object);
					
					virtual bool OnDropText(wxCoord x, wxCoord y, const wxString& data);

				private:
					Object* m_object;

				}; // DragTarget

			private:
				wxNotebook* m_parent;
				Object* m_object;

				wxTextCtrl* m_name;
				wxTextCtrl *m_x, *m_y;
				wxTextCtrl *m_width, *m_height;

			}; // ObjectPage
		}
	}
}

#endif // _GAME_FRUITS_VIEW_BACKSTAGE_OBJECT_PAGE_H_