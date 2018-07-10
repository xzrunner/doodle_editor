#ifndef _FEDITOR_SIMULATE_CLOTH_UI_CTRLS_MGR_H_
#define _FEDITOR_SIMULATE_CLOTH_UI_CTRLS_MGR_H_
#include "Edit/AbstractUICtrlsMgr.h"

class GLUI_FileBrowser;

namespace FEDITOR
{
	namespace SIMULATE_CLOTH
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
			void buildEditIrregularPanel(CmptMgr& cmptMgr, ShortcutKeyListener* shortcutLsn);
			void buildSettingsPanel();

		private:
			Blackboard* m_blackboard;

			static int m_openFileType;
				// 0 regular
				// 1 irregular

			static GLUI_FileBrowser* m_common_fb;

		}; // UICtrlsMgr 
	}
}

#endif // _FEDITOR_SIMULATE_CLOTH_UI_CTRLS_MGR_H_