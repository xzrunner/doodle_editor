#ifndef _FEDITOR_EXTRACT_EDGE_CONTROL_H_
#define _FEDITOR_EXTRACT_EDGE_CONTROL_H_
#include "Edit/AbstractControl.h"

namespace FEDITOR
{
	namespace EXTRACT_EDGE
	{
		class Control : public AbstractControl
		{
		public:
			Control();
			virtual ~Control();

			static AbstractControl* Create()
			{
				return new Control;
			}

		protected:
			virtual void onMouseRightDown(int x, int y);

			virtual void createEditCmpt();

			virtual void handleStep();
			virtual void handleUIEvent();

		}; // Control
	}
}

#endif // _FEDITOR_EXTRACT_EDGE_CONTROL_H_