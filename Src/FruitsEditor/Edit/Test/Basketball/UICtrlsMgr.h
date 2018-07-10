#ifndef _FEDITOR_BASKETBALL_UI_CTRLS_MGR_H_
#define _FEDITOR_BASKETBALL_UI_CTRLS_MGR_H_
#include "../../AbstractUICtrlsMgr.h"

namespace FEDITOR
{
	namespace BASKETBALL
	{
		class Blackboard;

		class UICtrlsMgr : public AbstractUICtrlsMgr
		{
		public:
			UICtrlsMgr(Blackboard* blackboard);

		public:
			virtual void createUIControls(CmptMgr& cmptMgr, ShortcutKeyListener* shortcutLsn); 

		private:
			static void callback(int id);

		private:
			Blackboard* m_blackboard;

		}; // UICtrlsMgr 
	}
}

#endif // _FEDITOR_BASKETBALL_UI_CTRLS_MGR_H_