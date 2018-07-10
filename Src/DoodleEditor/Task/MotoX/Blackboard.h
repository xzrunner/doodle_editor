#ifndef _DEDITOR_MOTOX_BLACKBOARD_H_
#define _DEDITOR_MOTOX_BLACKBOARD_H_

namespace deditor
{
	namespace motox
	{
		class Blackboard
		{
		public:
			static bool isCameraFocusOnMotobike;

			static const int gravity;
 			static const float wheelFriction, motoDensity, 
 				speed, acceleration, motoTorque;
 			static const float playerDensity, playerTorque;
 			static const float trackFriction;
			static const float frontWheelSpeedScale, frontWheelTorqueScale;

		}; // Blackboard
	}
}

#endif // _DEDITOR_MOTOX_BLACKBOARD_H_