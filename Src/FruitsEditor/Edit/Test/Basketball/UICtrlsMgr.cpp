#include "UICtrlsMgr.h"
#include "Blackboard.h"
#include "glui/glui.h"

using namespace FEDITOR;
using namespace FEDITOR::BASKETBALL;

UICtrlsMgr::UICtrlsMgr(Blackboard* blackboard)
{
	m_blackboard = blackboard;
}

void UICtrlsMgr::createUIControls(CmptMgr& cmptMgr, ShortcutKeyListener* shortcutLsn)
{
}

void UICtrlsMgr::callback(int id)
{
	switch (id)
	{
	}
}