#include "Control.h"
#include "View.h"
#include "Model.h"
#include "Blackboard.h"

#include "freeglut/freeglut.h"

using namespace FEDITOR::TEST_RENDERING;

Control::Control()
{
	m_view = new View();
	m_model = new Model(m_view->getBlackboard(), m_view);
}

Control::~Control()
{
}

void Control::createEditCmpt()
{
}

void Control::handleStep()
{
// 	static const int MAX_NUM = 200;
// 
// 	static std::queue<int> fps_buf;
// 	static int tot = 0;
// 
// 	static int last = 0;
// 	if (last != 0) 
// 	{
// 		int fps = (int) (1000.0f / (clock() - last));
// 		fps_buf.push(fps);
// 
// 		tot += fps;
// 		if (fps_buf.size() > MAX_NUM)
// 		{
// 			int top = fps_buf.front();	fps_buf.pop();
// 			tot -= top;
// 		}
// 
// 		std::cout << tot / MAX_NUM << std::endl;
// 	}
// 	last = clock();

	static int frame = 0,
		time,
		timebase = 0;

	frame++;
	time=glutGet(GLUT_ELAPSED_TIME);
	if (time - timebase > 1000) 
	{
		std::cout << frame*1000.0/(time-timebase) << std::endl;
		timebase = time;
		frame = 0;
	}

	m_model->handleEvent(Event(Blackboard::e_Step));
}

void Control::handleUIEvent()
{
	while (m_view->hasNextEvent())
	{
		Event event = m_view->getNextEvent();
		switch (event.getID())
		{
		case Blackboard::e_Open:
			m_model->handleEvent(event);
			break;
		}
	}
}