#ifndef _FEDITOR_MOTOX_JOINT_CONTROL_H_
#define _FEDITOR_MOTOX_JOINT_CONTROL_H_
#include "../../AbstractPhysCtrl.h"

namespace FEDITOR
{
	namespace MOTOX
	{
		namespace JOINT
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
				virtual void onMouseRightDown(int x, int y);

				virtual void createEditCmpt();

				virtual void handleStep();
				virtual void handleUIEvent();

				virtual void update();

			private:
				void setArrangeSpriteCommonOp();
				void setChooseJointPosOp();

			}; // Control
		}
	}
}

#endif // _FEDITOR_MOTOX_JOINT_CONTROL_H_