#ifndef _DEDITOR_AUTOMATIC_MERGE_DIRECTLY_ARRANGE_H_
#define _DEDITOR_AUTOMATIC_MERGE_DIRECTLY_ARRANGE_H_

#include "BaseStrategy.h"

namespace deditor
{
	namespace automatic_merge
	{
		class DirectlyArrange : public BaseStrategy
		{
		public:
			virtual void arrange(const std::vector<wxgui::ImageSprite*>& sprites, 
				int totWidth, int totHeight);

		}; // DirectlyArrange
	}
}

#endif // _DEDITOR_AUTOMATIC_MERGE_DIRECTLY_ARRANGE_H_