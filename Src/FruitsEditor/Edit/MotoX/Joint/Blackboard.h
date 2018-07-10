#ifndef _FEDITOR_MOTOX_JOINT_BLACKBOARD_H_
#define _FEDITOR_MOTOX_JOINT_BLACKBOARD_H_
#include "../../AbstractBlackboard.h"
#include "../ActorDefs.h"

namespace FEDITOR
{
	namespace MOTOX
	{
		namespace JOINT
		{
			class Blackboard : public AbstractBlackboard
			{
			public:
				Blackboard();

				enum
				{
					e_OpenHead = EVENT_ID_BASE_PRIVATE_BLACKBOARD,
					e_OpenBody,
					e_OpenBigArm,
					e_OpenSmallArm,
					e_OpenBigLeg,
					e_OpenSmallLeg,
					e_OpenFrontWheel,
					e_OpenBackWheel,
					e_OpenMotorbike,
					e_SetPartsAlive,
					e_CreateWheelsJoint,

					e_SetJointPos,
					e_CreateJoint,

					e_ResetJointNeck,
					e_ResetJointShoulder,
					e_ResetJointElbow,
					e_ResetJointHip,
					e_ResetJointKnee,
					e_SaveWholeParams,

					e_OpenWhole,
					e_SaveWhole
				};

			public:
				int m_partsAlive;
				int m_chooseJointID;

				JointParams m_jointParams[JOINTS_TYPE_COUNT];

			}; // Blackboard

			inline Blackboard::Blackboard()
			{
				m_partsAlive = 0;
				m_chooseJointID = 0;
			}
		}
	}
}

#endif // _FEDITOR_MOTOX_JOINT_BLACKBOARD_H_