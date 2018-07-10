#ifndef _FEDITOR_KEYBOARD_TEST_H_
#define _FEDITOR_KEYBOARD_TEST_H_
#include <Fruits2D/Fruits2D.h>

namespace FEDITOR
{
	enum KEY_TYPE
	{
		KEY_DELETE = 127
	};

	enum MY_KEY_TYPE
	{
		KEY_LEFT = 1024,
		KEY_RIGHT,
		KEY_UP,
		KEY_DOWN
	};

	class KeyBoardTest
	{
	public:
		static bool isShiftPress();
		static bool isCtrlPress();
		static bool isAltPress();

		static bool isLeftPress();
		static bool isRightPress();
		static bool isUpPress();
		static bool isDownPress();

	}; // KeyBoardTest
}

#endif // _FEDITOR_KEYBOARD_TEST_H_