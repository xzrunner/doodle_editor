#include "KeyboardTest.h"
#include "freeglut/freeglut.h"
#include <Windows.h>

using namespace FEDITOR;

bool KeyBoardTest::isShiftPress()
{
	return GetKeyState(VK_SHIFT) < 0;
}

bool KeyBoardTest::isCtrlPress()
{
	return GetKeyState(VK_CONTROL) < 0;
}

bool KeyBoardTest::isAltPress()
{
	return glutGetModifiers() == GLUT_ACTIVE_ALT;
}

bool KeyBoardTest::isLeftPress()
{
	return GetKeyState(VK_LEFT) < 0;
}

bool KeyBoardTest::isRightPress()
{
	return GetKeyState(VK_RIGHT) < 0;
}

bool KeyBoardTest::isUpPress()
{
	return GetKeyState(VK_UP) < 0;
}

bool KeyBoardTest::isDownPress()
{
	return GetKeyState(VK_DOWN) < 0;
}