#include "AEParamsOP.h"
#include "AEEditPanel.h"

using namespace deditor::motox;

AEParamsOP::AEParamsOP(AEEditPanel* editPanel)
	: DragPhysicsOP(editPanel, editPanel->getWorld(), editPanel->getGround()), 
	m_joints(editPanel->getJoints())
{

}

bool AEParamsOP::onKeyDown(int keyCode)
{
	if (DragPhysicsOP::onKeyDown(keyCode)) return true;

	switch (keyCode)
	{
 	//case 'a': case 'A':
 	//	break;
 	//case 'd': case 'D':
 	//	break;
 	//case 's': case 'S':
 	//	break;
 	//case 'w': case 'W':
 	//	break;

		// player to left
	case 'Z':
		m_joints.setJointMotion(e_PlayerToLeft);
		break;
		// player to middle
	case 'X':
		m_joints.setJointMotion(e_PlayerToMiddle);
		break;
		// player to right
	case 'C':
		m_joints.setJointMotion(e_PlayerToRight);
		break;
	}

	return false;
}
