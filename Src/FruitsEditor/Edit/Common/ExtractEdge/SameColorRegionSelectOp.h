#ifndef _FEDITOR_EXTRACT_EDGE_SAME_COLOR_REGION_SELECT_OP_H_
#define _FEDITOR_EXTRACT_EDGE_SAME_COLOR_REGION_SELECT_OP_H_
#include "Edit/EditOperation/AbstractOp.h"

namespace FEDITOR
{
	namespace EXTRACT_EDGE
	{
		class Model;

		class SameColorRegionSelectOp : public AbstractOp
		{
		public:
			SameColorRegionSelectOp(AbstractControl* task, Model* model);

			virtual void onMouseLeftDown(int x, int y);
			virtual bool onMouseRightDown(int x, int y);

		private:
			Model* m_model;

		}; // SameColorRegionSelectOp
	}
}

#endif // _FEDITOR_EXTRACT_EDGE_SAME_COLOR_REGION_SELECT_OP_H_