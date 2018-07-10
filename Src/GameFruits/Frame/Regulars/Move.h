#ifndef _GAME_FRUITS_REGULAR_MOVE_H_
#define _GAME_FRUITS_REGULAR_MOVE_H_
#include "RegularListItem.h"

namespace GAME_FRUITS
{
	namespace REGULAR
	{
		class Move : public RegularListItem
		{
		public:
			Move();

		protected:
			virtual wxSizer* createExtend(wxWindow* extend);

		private:
			wxSizer* createAngleSetting(wxWindow* extend);
			wxSizer* createSpeedSetting(wxWindow* extend);

		private:
			wxTextCtrl* m_angle;
			wxTextCtrl* m_speed;

		}; // Move
	}
}

#endif // _GAME_FRUITS_REGULAR_MOVE_H_