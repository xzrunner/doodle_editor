#include "Control.h"
#include "Blackboard.h"
#include "View.h"
#include "Model.h"
#include "ChooseJointPosOp.h"
#include "ControlMotionOp.h"
#include "ArrangeSpriteCB.h"
#include "../Utility.h"
#include "../../EditOperation/ArrangeSpriteCommonOp.h"
#include "../../../Dataset/Body.h"
#include "../../../Dataset/BodyFactory.h"
#include "../../../Dataset/LayersMgr.h"

using namespace FEDITOR;
using namespace FEDITOR::MOTOX::JOINT;

Control::Control()
{
	m_view = new View(MOTOX::SCALE_SCREEN_TO_PHYSICS);
	m_model = new Model(m_view->getBlackboard(), getWorld());

	BodyFactory::setWorld(getWorld());

	setArrangeSpriteCommonOp();
}

Control::~Control()
{
}

void Control::onMouseRightDown(int x, int y)
{
	if (m_editOp) 
	{
		bool handled = m_editOp->onMouseRightDown(x, y);
		if (!handled) setArrangeSpriteCommonOp();
	}
}

void Control::createEditCmpt()
{
	AbstractPhysCtrl::createEditCmpt();
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
		case Blackboard::e_OpenHead:
		case Blackboard::e_OpenBody:
		case Blackboard::e_OpenBigArm:
		case Blackboard::e_OpenSmallArm:
		case Blackboard::e_OpenBigLeg:
		case Blackboard::e_OpenSmallLeg:
		case Blackboard::e_OpenFrontWheel:
		case Blackboard::e_OpenBackWheel:
		case Blackboard::e_OpenMotorbike:
		case Blackboard::e_SetPartsAlive:
			m_model->handleEvent(event);
			break;

		case Blackboard::e_SetJointPos:
			setChooseJointPosOp();
			break;
		case Blackboard::e_CreateJoint:
		case Blackboard::e_CreateWheelsJoint:
			m_model->handleEvent(event);
			break;

		case Blackboard::e_ResetJointNeck:
		case Blackboard::e_ResetJointShoulder:
		case Blackboard::e_ResetJointElbow:
		case Blackboard::e_ResetJointHip:
		case Blackboard::e_ResetJointKnee:
		case Blackboard::e_SaveWholeParams:
			m_model->handleEvent(event);
			break;

		case Blackboard::e_OpenWhole:
		case Blackboard::e_SaveWhole:
			m_model->handleEvent(event);
			break;
		}
	}
}

void Control::update()
{
	AbstractPhysCtrl::update();
	m_model->getLayersMgr().updateEachFrame();
}

void Control::setArrangeSpriteCommonOp()
{
	Model* model = static_cast<Model*>(m_model);
	Layer* layer = model->getEditedLayer();
	ArrangeSpriteCB* callback = new ArrangeSpriteCB(model->getParts());
	AbstractOp* supplement = new ControlMotionOp(this, model->getJoints());
	if (m_editOp) delete m_editOp;
	m_editOp = new ArrangeSpriteCommonOp(this, layer, getWorld(), model->getGround()->getBody(), 
		ArrangeSpritePhysOp::e_MouseOn, callback, supplement);
}

void Control::setChooseJointPosOp()
{
	Model* model = static_cast<Model*>(m_model);
	if (m_editOp) delete m_editOp;
	AbstractOp* supplement = new ControlMotionOp(this, model->getJoints());
	m_editOp = new ChooseJointPosOp(this, model->getJointPos(), supplement);
}