#include "ControlMotionOp.h"
#include "Joints.h"

using namespace FEDITOR;
using namespace FEDITOR::MOTOX::JOINT;

ControlMotionOp::ControlMotionOp(AbstractControl* task, Joints& joints)
	: AbstractOp(task), m_joints(joints)
{
}

void ControlMotionOp::onKeyboard(unsigned char key)
{
	switch (key)
	{
		// shoulder
	case '1':
		m_joints.setJointMotion(e_JointTypeShoulder, false);
		break;
	case '2':
		m_joints.setJointMotion(e_JointTypeShoulder, true);
		break;
		// elbow
	case '3':
		m_joints.setJointMotion(e_JointTypeElbow, false);
		break;
	case '4':
		m_joints.setJointMotion(e_JointTypeElbow, true);
		break;
		// hip
	case '5':
		m_joints.setJointMotion(e_JointTypeHip, false);
		break;
	case '6':
		m_joints.setJointMotion(e_JointTypeHip, true);
		break;
		// knee
	case '7':
		m_joints.setJointMotion(e_JointTypeKnee, false);
		break;
	case '8':
		m_joints.setJointMotion(e_JointTypeKnee, true);
		break;
		// neck
	case '9':
		m_joints.setJointMotion(e_JointTypeNeck, false);
		break;
	case '0':
		m_joints.setJointMotion(e_JointTypeNeck, true);
		break;
		// hand
	case 'a':
		m_joints.setJointMotion(e_JointTypeHand, false);
		break;
	case 's':
		m_joints.setJointMotion(e_JointTypeHand, true);
		break;
		// foot
	case 'd':
		m_joints.setJointMotion(e_JointTypeFoot, false);
		break;
	case 'f':
		m_joints.setJointMotion(e_JointTypeFoot, true);
		break;

		// player to left
	case 'z':
		m_joints.setJointMotion(e_PlayerToLeft);
		break;
		// player to middle
	case 'x':
		m_joints.setJointMotion(e_PlayerToMiddle);
		break;
		// player to right
	case 'c':
		m_joints.setJointMotion(e_PlayerToRight);
		break;
	}
}