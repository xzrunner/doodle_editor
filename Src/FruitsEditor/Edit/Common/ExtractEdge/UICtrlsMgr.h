#ifndef _FEDITOR_EXTRACT_EDGE_UI_CTRLS_MGR_H_
#define _FEDITOR_EXTRACT_EDGE_UI_CTRLS_MGR_H_
#include "Edit/AbstractUICtrlsMgr.h"

class GLUI_FileBrowser;

namespace FEDITOR
{
	namespace EXTRACT_EDGE
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
			void buildInputPanel();
			void buildCoordLinesPanel();
			void buildEditorPanel(CmptMgr& cmptMgr, ShortcutKeyListener* shortcutLsn);
			void buildAutoPanel();

		private:
			Blackboard* m_blackboard;

			static GLUI_FileBrowser* m_background_fb;

		}; // UICtrlsMgr 
	}
}

#endif // _FEDITOR_EXTRACT_EDGE_UI_CTRLS_MGR_H_