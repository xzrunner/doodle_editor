#ifndef _FEDITOR_EXTRACT_EDGE_OUTPUT_COORDS_OPERATION_H_
#define _FEDITOR_EXTRACT_EDGE_OUTPUT_COORDS_OPERATION_H_
#include "Edit/EditOperation/AbstractOp.h"

namespace FEDITOR
{
	namespace EXTRACT_EDGE
	{
		class Model;

		class OutputCoordsOp : public AbstractOp
		{
		public:
			OutputCoordsOp(AbstractControl* task, Model* model);

			virtual void onMouseLeftDown(int x, int y);

		private:
			Model* m_model;

		}; // OutputCoordsOp
	}
}

#endif /// _FEDITOR_EXTRACT_EDGE_OUTPUT_COORDS_OPERATION_H_