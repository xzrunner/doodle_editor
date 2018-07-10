#include "SameColorRegionSelectOp.h"
#include "Model.h"
#include "SameColorRegionSelect.h"

using namespace FEDITOR;
using namespace FEDITOR::EXTRACT_EDGE;

SameColorRegionSelectOp::SameColorRegionSelectOp(AbstractControl* task, Model* model)
	: AbstractOp(task)
{
	m_model = model;
}

void SameColorRegionSelectOp::onMouseLeftDown(int x, int y)
{
	if (m_model->getAutoSelect())
	{
		m_model->getAutoSelect()->selectByPos(getMousePos(x, y));
		m_model->refreshAutoSelectLayer();
	}
}

bool SameColorRegionSelectOp::onMouseRightDown(int x, int y)
{
	return false;
}