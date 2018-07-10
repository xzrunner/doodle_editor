#ifndef _GAME_FRUITS_REGULAR_MOUSE_PRESS_H_
#define _GAME_FRUITS_REGULAR_MOUSE_PRESS_H_
#include "RegularListItem.h"
#include "Frame/View/Backstage/DragRegularTarget.h"
#include <Fruits2D/Fruits2D.h>

namespace GAME_FRUITS
{
	namespace REGULAR
	{
		class MousePress : public RegularListItem
		{
		public:
			MousePress();

			void addRegular(RegularListItem* regular, bool isImpl);

			bool isDownChange() const;

			const std::vector<RegularListItem*>& getAllRegulars(bool isImpl) const;

		protected:
			virtual wxSizer* createExtend(wxWindow* extend);

		private:
			wxSizer* createMouseStateListItem(wxWindow* extend);
			wxSizer* createImplItem(wxWindow* extend);
			wxSizer* createNotImplItem(wxWindow* extend);

		private:
			class DragTarget : public VIEW::BACKSTAGE::DragRegularTarget
			{
			public:
				DragTarget(wxWindow* parent, MousePress* mousePress, bool isImpl);

				virtual bool OnDropText(wxCoord x, wxCoord y, const wxString& data);

			private:
				MousePress* m_mousePress;
				bool m_isImpl;

			}; // DragTarget

		private:
			wxChoice* m_stateList;

			std::vector<RegularListItem*> m_implList;
			std::vector<RegularListItem*> m_noImplList;

			wxWindow *m_extendImpl, *m_extendNoImpl;

		}; // MousePress
	}
}

#endif // _GAME_FRUITS_REGULAR_MOUSE_PRESS_H_