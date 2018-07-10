#ifndef _FEDITOR_SKATER_UI_CONTROL_MANAGER_H_
#define _FEDITOR_SKATER_UI_CONTROL_MANAGER_H_
#include "Edit/AbstractUICtrlsMgr.h"

class GLUI_FileBrowser;
class GLUI_Panel;

namespace FEDITOR
{
	namespace SKATER
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
			void buildSettingPanel(CmptMgr& cmptMgr, ShortcutKeyListener* shortcutLsn);
			void buildSetTexCoordPanel(GLUI_Panel* parent);


		private:
			Blackboard* m_blackboard;

			static int m_openFileType;
				// 0 Background
				// 1 Tile Sprite
				// 2 Level
				// 3 Old Version
				// 4 Sprite Bound

			static GLUI_FileBrowser* m_common_fb;

		}; // UICtrlsMgr
	}
}

#endif // _FEDITOR_SKATER_UI_CONTROL_MANAGER_H_