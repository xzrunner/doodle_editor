#include "OutputCoordsOp.h"
#include "Model.h"

using namespace FEDITOR;
using namespace FEDITOR::EXTRACT_EDGE;

OutputCoordsOp::OutputCoordsOp(AbstractControl* task, Model* model)
	: AbstractOp(task)
{
	m_model = model;
}

void OutputCoordsOp::onMouseLeftDown(int x, int y)
{
	const f2Vec2 src = getMousePos(x, y);
	const f2Vec2 dst = m_model->getCoordsInCurrentType(src);
	std::cout << dst.x << " " << dst.y << std::endl;
}