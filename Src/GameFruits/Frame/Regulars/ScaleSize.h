#ifndef _GAME_FRUITS_REGULAR_SCALE_SIZE_H_
#define _GAME_FRUITS_REGULAR_SCALE_SIZE_H_
#include "RegularListItem.h"

namespace GAME_FRUITS
{
	namespace REGULAR
	{
		class ScaleSize : public RegularListItem
		{
		public:
			ScaleSize();

			float getScaleValue() const;

		protected:
			virtual wxSizer* createExtend(wxWindow* extend);

		private:
			wxSizer* createSetValueItem(wxWindow* extend);

		private:
			wxSpinCtrl* m_scaleCtrl;

		}; // ScaleSize
	}
}

#endif // _GAME_FRUITS_REGULAR_SCALE_SIZE_H_