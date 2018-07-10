#ifndef _GAME_FRUITS_REGULAR_CHANGE_IMAGE_H_
#define _GAME_FRUITS_REGULAR_CHANGE_IMAGE_H_
#include "RegularListItem.h"

namespace GAME_FRUITS
{
	namespace REGULAR
	{
		class ChangeImage : public RegularListItem
		{
		public:
			ChangeImage();

			wxString getImagePath() const;

		protected:
			virtual wxSizer* createExtend(wxWindow* extend);

		private:
			wxSizer* createChooseListItem(wxWindow* extend);

		private:
			wxChoice* m_selectList;

		}; // ChangeImage
	}
}

#endif // _GAME_FRUITS_REGULAR_CHANGE_IMAGE_H_