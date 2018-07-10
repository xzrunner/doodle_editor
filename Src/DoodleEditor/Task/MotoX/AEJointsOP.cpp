#include "AEJointsOP.h"
#include "AEEditPanel.h"
#include "AEJoints.h"
#include "AEJointsCMPT.h"

using namespace deditor::motox;

AEJointsOP::AEJointsOP(AEEditPanel* editPanel, AEJointsCMPT* cmpt)
	: ZoomViewOP(editPanel, true), m_joints(editPanel->getJoints())
{
	m_cmpt = cmpt;
}

bool AEJointsOP::onMouseLeftDown(int x, int y)
{
	if (wxgui::ZoomViewOP::onMouseLeftDown(x, y)) return true;

	createJoint(x, y);
	m_editPanel->Refresh();

	return false;
}

bool AEJointsOP::onMouseDrag(int x, int y)
{
	if (wxgui::ZoomViewOP::onMouseDrag(x, y)) return true;

	createJoint(x, y);
	m_editPanel->Refresh();

	return false;
}

bool AEJointsOP::onDraw() const
{
	if (wxgui::ZoomViewOP::onDraw()) return true;

	m_joints.onDraw();

	return false;
}

void AEJointsOP::createJoint(int x, int y)
{
	f2Vec2 pos = m_editPanel->transPosScreenToProject(x, y);

	AEEditPanel* editPanel = static_cast<AEEditPanel*>(m_editPanel);
	editPanel->getJoints().createJoint(m_cmpt->getSelectedID(), pos);
}