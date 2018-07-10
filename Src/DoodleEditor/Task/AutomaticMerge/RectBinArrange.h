#ifndef _DEDITOR_AUTOMATIC_MERGE_RECT_BIN_ARRANGE_H_
#define _DEDITOR_AUTOMATIC_MERGE_RECT_BIN_ARRANGE_H_

#include "BaseStrategy.h"

namespace deditor
{
	namespace automatic_merge
	{
		class RectBinArrange : public BaseStrategy
		{
		public:
			virtual void arrange(const std::vector<wxgui::ImageSprite*>& sprites, 
				int totWidth, int totHeight);

		}; // RectBinArrange
	}
}

#endif // _DEDITOR_AUTOMATIC_MERGE_RECT_BIN_ARRANGE_H_