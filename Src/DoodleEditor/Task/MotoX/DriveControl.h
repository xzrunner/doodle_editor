#ifndef _DEDITOR_MOTOX_DRIVE_CONTROL_H_
#define _DEDITOR_MOTOX_DRIVE_CONTROL_H_

namespace deditor
{
	namespace motox
	{
		struct DriveControl
		{
			enum SPEED 
			{
				FORWARD,
				BACK,
				STOP
			};
			enum TILT 
			{
				LEFT,
				MIDDLE,
				RIGHT
			};

			SPEED speed;
			TILT tilt;

			DriveControl();

		}; // DriveControl 

		inline DriveControl::DriveControl()
		{
			speed = STOP;
			tilt = MIDDLE;
		}
	}
}

#endif // _DEDITOR_MOTOX_DRIVE_CONTROL_H_