#include "DemoBase.h"
#include "Blackboard.h"

using namespace FEDITOR::SOFT_RENDER;

DemoBase::DemoBase(Blackboard* bb)
{
	m_camera.init(0, bb->m_camPos, bb->m_camDir, NULL, 50, 500, 90, 800, 600);
}

DemoBase::~DemoBase()
{

}

F3D::f3Camera4& DemoBase::getCamera()
{
	return m_camera;
}