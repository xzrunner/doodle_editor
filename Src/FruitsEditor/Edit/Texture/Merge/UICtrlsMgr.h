#ifndef _FEDITOR_TEXTURE_MERGE_UI_CONTROL_MANAGER_H_
#define _FEDITOR_TEXTURE_MERGE_UI_CONTROL_MANAGER_H_
#include "Edit/AbstractUICtrlsMgr.h"

class GLUI_FileBrowser;

namespace FEDITOR
{
	namespace TEXTURE_MERGE
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
			void buildBgPanel();
			void buildIOPanel();
			void buildEditPanel();

		private:
			Blackboard* m_blackboard;

			static GLUI_FileBrowser* m_common_fb;

		}; // UICtrlsMgr
	}
}

#endif // _FEDITOR_TEXTURE_MERGE_UI_CONTROL_MANAGER_H_