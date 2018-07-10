#ifndef _FEDITOR_CMPT_MGR_H_
#define _FEDITOR_CMPT_MGR_H_
#include <Fruits2D/Fruits2D.h>

class GLUI_Node;

namespace FEDITOR
{
	class AbstractCmpt;
	class ShortcutKeyListener;

	class CmptMgr
	{
	public:
		~CmptMgr();

		void push(AbstractCmpt* item);

		void createUIControls(GLUI_Node* parent, int type, ShortcutKeyListener* shortcutLsn = NULL);

		void handleUIEvent();

	private:
		typedef std::map<int, AbstractCmpt*> CONTAINER;

	private:
		CONTAINER m_items;

	}; // CmptMgr
}

#endif // _FEDITOR_CMPT_MGR_H_