#ifndef _FEDITOR_SIMULATE_CLOTH_CONTROL_H_
#define _FEDITOR_SIMULATE_CLOTH_CONTROL_H_
#include "Edit/AbstractPhysCtrl.h"

namespace FEDITOR
{
	namespace SIMULATE_CLOTH
	{
		class Control : public AbstractPhysCtrl
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

#endif // _FEDITOR_SIMULATE_CLOTH_CONTROL_H_