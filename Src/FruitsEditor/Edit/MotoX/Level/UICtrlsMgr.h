#ifndef _FEDITOR_MOTOX_LEVEL_UI_CTRLS_MGR_H_
#define _FEDITOR_MOTOX_LEVEL_UI_CTRLS_MGR_H_
#include "../../AbstractUICtrlsMgr.h"

class GLUI_FileBrowser;

namespace FEDITOR
{
	namespace MOTOX
	{
		namespace LEVEL
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
				void buildSettingPanel(CmptMgr& cmptMgr);
				void buildOpenPanel();
				void buildTrackChainPanel(CmptMgr& cmptMgr);
				void buildTilesPanel();
				void buildActorSettingPanel();

			private:
				Blackboard* m_blackboard;

				static int m_openFileType;
					// 0 Background Texture
					// 1 Background Shapes, tris with color
					// 2 Track Chains
					// 3 Tile
					// 4 Motorbike
					// 5 All Sprites

				static GLUI_FileBrowser* m_common_fb;

			}; // UICtrlsMgr
		}
	}
}

#endif // _FEDITOR_MOTOX_LEVEL_UI_CTRLS_MGR_H_