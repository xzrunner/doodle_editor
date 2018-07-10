#ifndef _FEDITOR_BASKETBALL_CONTROL_H_
#define _FEDITOR_BASKETBALL_CONTROL_H_
#include "../../AbstractPhysCtrl.h"

namespace FEDITOR
{
	namespace BASKETBALL
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

#endif // _FEDITOR_BASKETBALL_CONTROL_H_