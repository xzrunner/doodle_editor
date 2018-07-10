#ifndef _FEDITOR_MOTOX_DRIVE_CONTROL_H_
#define _FEDITOR_MOTOX_DRIVE_CONTROL_H_

namespace FEDITOR
{
	namespace MOTOX
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

#endif // _FEDITOR_MOTOX_DRIVE_CONTROL_H_