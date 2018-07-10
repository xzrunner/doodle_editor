#ifndef _FEDITOR_MOTOX_PACKAGE_UI_CONTROL_MANAGER_H_
#define _FEDITOR_MOTOX_PACKAGE_UI_CONTROL_MANAGER_H_
#include "Edit/AbstractUICtrlsMgr.h"

class GLUI_FileBrowser;

namespace FEDITOR
{
	namespace MOTOX
	{
		namespace PACKAGE
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

				enum
				{
					e_OpenFile = EVENT_ID_BASE_PRIVATE_UI_CTRLS_MGR
				};

			private:
				void buildIOPanel();

			private:
				Blackboard* m_blackboard;

				static int m_openFileType;
				// 0 Track Chains
				// 1 Actor

				static GLUI_FileBrowser* m_common_fb;

			}; // UICtrlsMgr
		}
	}
}

#endif // _FEDITOR_MOTOX_PACKAGE_UI_CONTROL_MANAGER_H_