#ifndef _FEDITOR_FILL_COLOR_UI_CTRLS_MGR_H_
#define _FEDITOR_FILL_COLOR_UI_CTRLS_MGR_H_
#include "Edit/AbstractUICtrlsMgr.h"

class GLUI_FileBrowser;

namespace FEDITOR
{
	namespace FILL_COLOR
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
				e_OpenFile = EVENT_ID_BASE_PRIVATE_UI_CTRLS_MGR,
				e_SaveFile
			};

		private:
			void buildIOPanel();
			void buildColorPanel(CmptMgr& cmptMgr);
			void buildSettingPanel();

		private:
			Blackboard* m_blackboard;

			static int m_openFileType;
				// 0 Chains
				// 1 Triangles
				// 2 Image
				// 3 Fill
			static int m_saveFileType;
				// 0 Color Tris
				// 1 Fill Chains with name

			static GLUI_FileBrowser* m_common_fb;

		}; // UICtrlsMgr 
	}
}

#endif // _FEDITOR_FILL_COLOR_UI_CTRLS_MGR_H_