#include "ChooseJointPosOp.h"
#include "../../../Dataset/PointShape.h"

using namespace FEDITOR;
using namespace FEDITOR::MOTOX::JOINT;

ChooseJointPosOp::ChooseJointPosOp(AbstractControl* task, PointShape* point, AbstractOp* supplement)
	: AbstractOp(task, supplement)
{
	m_point = point;
}

void ChooseJointPosOp::onMouseLeftDown(int x, int y)
{
	m_point->m_pos = getMousePos(x, y);
}