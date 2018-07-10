#include "Control.h"
#include "View.h"
#include "Model.h"
#include "Blackboard.h"

using namespace FEDITOR::SOFT_RENDER;

Control::Control()
{
	m_view = new View();
	m_model = new Model(m_view->getBlackboard());
}

Control::~Control()
{
}

void Control::createEditCmpt()
{
}

void Control::handleStep()
{
}

void Control::handleUIEvent()
{
	while (m_view->hasNextEvent())
	{
		Event event = m_view->getNextEvent();
		switch (event.getID())
		{
		}
	}
}