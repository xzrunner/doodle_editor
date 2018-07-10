#ifndef _FEDITOR_MOTOX_JOINT_CHOOSE_JOINT_POS_OP_H_
#define _FEDITOR_MOTOX_JOINT_CHOOSE_JOINT_POS_OP_H_
#include "../../EditOperation/AbstractOp.h"

namespace FEDITOR
{
	class PointShape;

	namespace MOTOX
	{
		namespace JOINT
		{
			class ChooseJointPosOp : public AbstractOp
			{
			public:
				ChooseJointPosOp(AbstractControl* task, PointShape* point, AbstractOp* supplement);

				virtual void onMouseLeftDown(int x, int y);

			private:
				PointShape* m_point;

			}; // ChooseJointPosOp
		}
	}
}

#endif // _FEDITOR_MOTOX_JOINT_CHOOSE_JOINT_POS_OP_H_