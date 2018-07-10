#ifndef _MOTOX_ACTOR_DEFINES_H_
#define _MOTOX_ACTOR_DEFINES_H_

#ifdef D2D_ANDROID_NATIVE
#include <Doodle2D/doodle2d.h>
#endif

#include <cstdlib>

namespace motox
{
	static const size_t PLAYER_PARTS_COUNT		= 10;
	static const size_t MOTORBIKE_PARTS_COUNT	= 5;
	static const size_t PARTS_COUNT				= PLAYER_PARTS_COUNT + MOTORBIKE_PARTS_COUNT;
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
		e_PartBackWheel = e_PartSmallLegRight + 1,
		e_PartFrontWheel,
		e_PartMotorBody,
		e_PartBackDamping,
		e_PartFrontDamping
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
}

#endif // _MOTOX_ACTOR_DEFINES_H_