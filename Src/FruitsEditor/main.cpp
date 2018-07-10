#include "glui/glui.h"
#include "SOIL/SOIL.h"

#include "Edit/AbstractControl.h"

using namespace FEDITOR;

int taskIndex = 1;
int taskSelection = 1;
int taskCount = 0;
TaskEntry* entry;
AbstractControl* task;

float xy_aspect;
int vx, vy, vw, vh;
int framePeriod = 16;
int main_window;
GLUI* menu;

float settingsHz = 60.0;

extern TaskEntry g_taskEntries[];

// This is used to control the frame rate (60Hz).
void Timer(int)
{
	glutSetWindow(main_window);
	glutPostRedisplay();
	glutTimerFunc(framePeriod, Timer, 0);
}

void display()
{
	glClearColor(0.9f, 0.9f, 0.9f, 1.0f);
	//	glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	task->step();

	glutSwapBuffers();

	if (taskSelection != taskIndex)
	{
		taskIndex = taskSelection;
		delete task;
		entry = g_taskEntries + taskIndex;
		task = entry->createFcn();
		task->createUIFrame(main_window);
	}
}

void reshape(int x, int y)
{
	int vx, vy, vw, vh;
	GLUI_Master.get_viewport_area(&vx, &vy, &vw, &vh);
	glViewport(vx, vy, vw, vh);

	task->reshape(x, y, vw, vh);

	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
		// ...

	default:
		task->onKeyboard(key, x, y);
	}
}

void keyboardSpecial(int key, int x, int y)
{
	switch (key)
	{
		// ...

	default:
		task->onKeyboardSpecial(key, x, y);
	}
}

void mouse(int button, int state, int x, int y)
{
	if (taskSelection != taskIndex)
	{
		glutPostRedisplay();
	}

	task->onMouseButton(button, state, x, y);
}

void mouseMotion(int x, int y)
{
	task->onMouseDrag(x, y);
}

void mouseMotionPassive(int x, int y)
{
	task->onMouseMove(x, y);
}

void mouseWheel(int wheel, int direction, int x, int y)
{
	task->onMouseWheel(direction, x, y);
}

int main(int argc, char* argv[])
{


	/****************************************/
	/*			Initialize Task				*/
	/****************************************/
	taskCount = 0;
	while (g_taskEntries[taskCount].name != NULL)
	{
		++taskCount;
	}

	taskIndex = F2D::f2Clamp(taskIndex, 0, taskCount - 1);
	taskSelection = taskIndex;

	entry = g_taskEntries + taskIndex;
	task = entry->createFcn();

	/****************************************/
	/*   Initialize GLUT and create window  */
	/****************************************/
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(800, 600);

	main_window = glutCreateWindow("Fruits Editor");

	glEnable(GL_TEXTURE_2D);

	glutDisplayFunc(display);
	//	glutReshapeFunc(reshape);
	GLUI_Master.set_glutReshapeFunc(reshape);
	// 	GLUI_Master.set_glutKeyboardFunc(keyboard);
	// 	GLUI_Master.set_glutSpecialFunc(keyboardSpecial);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(keyboardSpecial);
	glutMouseFunc(mouse);
	glutMotionFunc(mouseMotion);
	glutPassiveMotionFunc(mouseMotionPassive);
	glutMouseWheelFunc(mouseWheel);

	task->createUIFrame(main_window);

	/****************************************/
	/*         Here's the GLUI code         */
	/****************************************/
	menu = GLUI_Master.create_glui_subwindow(main_window, GLUI_SUBWINDOW_TOP);

	GLUI_Listbox* taskList;
	size_t taskCount = 0;
	TaskEntry* e = g_taskEntries;
	while (e->name || e->createFcn)
	{
		if (!e->createFcn)
		{
			if (e != g_taskEntries) new GLUI_Column(menu, true);
			taskList = new GLUI_Listbox(menu, e->name, &taskSelection);
		}
		else
		{
			taskList->add_item(taskCount, e->name);
		}
		++taskCount;
		++e;
	}

	glutTimerFunc(framePeriod, Timer, 0);

	glutMainLoop();

	return 0;
}