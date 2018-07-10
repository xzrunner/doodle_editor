#ifndef _FEDITOR_MOTOX_ACTOR_DEFINES_H_
#define _FEDITOR_MOTOX_ACTOR_DEFINES_H_
#include <Fruits2D/Fruits2D.h>

namespace FEDITOR
{
	namespace MOTOX
	{
		static const size_t PLAYER_PARTS_COUNT		= 10;
		static const size_t MOTORBIKE_PARTS_COUNT	= 3;
		static const size_t JOINTS_COUNT			= 13;
		static const size_t JOINTS_TYPE_COUNT		= 7;

		enum PLAYER_PART
		{
			e_PartHead,
			e_PartBody,
			e_PartBigArmLeft,
			e_PartBigArmRight,
			e_PartSmallArmLeft,
			e_PartSmallArmRight,
			e_PartBigLegLeft,
			e_PartBigLegRight,
			e_PartSmallLegLeft,
			e_PartSmallLegRight
		};

		enum MOTORBIKE_PART
		{
			e_PartFrontWheel = e_PartSmallLegRight + 1,
			e_PartBackWheel,
			e_PartMotorBody
		};

		enum ACTOR_JOINT
		{
			e_JointNeck,
			e_JointShoulderL,
			e_JointShoulderR,
			e_JointElbowL,
			e_JointElbowR,
			e_JointHipL,
			e_JointHipR,
			e_JointKneeL,
			e_JointKneeR,		
			e_JointHandL,		
			e_JointHandR,		
			e_JointFootL,		
			e_JointFootR	
		};

		enum ACTOR_JOINT_TYPE
		{
			e_JointTypeNeck,
			e_JointTypeShoulder,
			e_JointTypeElbow,
			e_JointTypeHip,
			e_JointTypeKnee,	
			e_JointTypeHand,	
			e_JointTypeFoot
		};

		enum PLAYER_STATE
		{
			e_PlayerStateLeft,
			e_PlayerStateMiddle,
			e_PlayerStateRight
		};

		enum PLAYER_MOTION
		{
			e_PlayerToLeft,
			e_PlayerToMiddle,
			e_PlayerToRight
		};

		struct JointParams
		{
			float positive_speed, negative_speed;
			float left_angle, mid_angle, right_angle;
			float max_torque;

			int enableLimit, enableMotor;

			JointParams();

		}; // JointParams 

		inline JointParams::JointParams()
		{
			positive_speed = 2.0f;
			negative_speed = -2.0f;
			max_torque = 0.0f;

			enableLimit = enableMotor = 1;
		}

		inline std::istream& operator >> (std::istream& is, JointParams& params)
		{
			is >> params.positive_speed >> params.negative_speed
				>> params.left_angle >> params.mid_angle >> params.right_angle
				>> params.max_torque;
			return is;
		}

		inline std::ostream& operator << (std::ostream& os, const JointParams& params)
		{
			os << params.positive_speed << " " << params.negative_speed << " "
				<< params.left_angle << " " << params.mid_angle << " " << params.right_angle << " "
				<< params.max_torque;
			return os;
		}
	}
}

#endif // _FEDITOR_MOTOX_ACTOR_DEFINES_H_