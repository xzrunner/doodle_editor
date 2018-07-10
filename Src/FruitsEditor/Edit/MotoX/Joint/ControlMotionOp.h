#ifndef _FEDITOR_MOTOX_JOINT_CONTROL_MOTION_OP_H_
#define _FEDITOR_MOTOX_JOINT_CONTROL_MOTION_OP_H_
#include "../../EditOperation/AbstractOp.h"

namespace FEDITOR
{
	namespace MOTOX
	{
		namespace JOINT
		{
			class Joints;

			class ControlMotionOp : public AbstractOp
			{
			public:
				ControlMotionOp(AbstractControl* task, Joints& joints);

				virtual void onKeyboard(unsigned char key);

			private:
				Joints& m_joints;

			}; // ControlMotionOp
		}
	}
}

#endif // _FEDITOR_MOTOX_JOINT_CONTROL_MOTION_OP_H_