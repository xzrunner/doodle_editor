#ifndef _FEDITOR_COMPOSE_IMG_UI_CTRLS_MGR_H_
#define _FEDITOR_COMPOSE_IMG_UI_CTRLS_MGR_H_
#include "Edit/AbstractUICtrlsMgr.h"

class GLUI_FileBrowser;

namespace FEDITOR
{
	namespace COMPOSE_IMG
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
			void buildOpenPanel();

		private:
			Blackboard* m_blackboard;

			static int m_openFileType;
				// 0 Background
				// 1 Tile Sprite
				// 2 Level

			static GLUI_FileBrowser* m_common_fb;

		}; // UICtrlsMgr 
	}
}

#endif // _FEDITOR_COMPOSE_IMG_UI_CTRLS_MGR_H_