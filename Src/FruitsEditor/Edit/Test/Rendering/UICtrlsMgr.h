#ifndef _FEDITOR_TEST_RENDERING_UI_CONTROL_MANAGER_H_
#define _FEDITOR_TEST_RENDERING_UI_CONTROL_MANAGER_H_
#include "Edit/AbstractUICtrlsMgr.h"

class GLUI_FileBrowser;

namespace FEDITOR
{
	namespace TEST_RENDERING
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
			void buildIOPanel();
			void buildSettingPanel();

		private:
			Blackboard* m_blackboard;

			static GLUI_FileBrowser* m_common_fb;

		}; // UICtrlsMgr
	}
}

#endif // _FEDITOR_TEST_RENDERING_UI_CONTROL_MANAGER_H_