#ifndef _FEDITOR_MOTOX_PACKAGE_CONTROL_H_
#define _FEDITOR_MOTOX_PACKAGE_CONTROL_H_
#include "Edit/AbstractControl.h"

namespace FEDITOR
{
	namespace MOTOX
	{
		namespace PACKAGE
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
}

#endif // _FEDITOR_MOTOX_PACKAGE_CONTROL_H_