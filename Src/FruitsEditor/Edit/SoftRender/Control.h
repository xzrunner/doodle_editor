#ifndef _FEDITOR_SOFT_RENDER_CONTROL_H_
#define _FEDITOR_SOFT_RENDER_CONTROL_H_
#include "FruitsEditor/Edit/AbstractControl.h"

namespace FEDITOR
{
	namespace SOFT_RENDER
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
			virtual void createEditCmpt();

			virtual void handleStep();
			virtual void handleUIEvent();

		}; // Control
	}
}

#endif // _FEDITOR_SOFT_RENDER_CONTROL_H_