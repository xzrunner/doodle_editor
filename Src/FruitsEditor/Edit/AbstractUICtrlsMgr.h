#ifndef _FEDITOR_ABSTRACT_UI_CTRLS_MGR_H_
#define _FEDITOR_ABSTRACT_UI_CTRLS_MGR_H_
#include "Utility.h"

class GLUI;

namespace FEDITOR
{
	class CmptMgr;
	class ShortcutKeyListener;

	class AbstractUICtrlsMgr
	{
	public:
		AbstractUICtrlsMgr();
		virtual ~AbstractUICtrlsMgr();

		void createUIRoot(int mainWnd);
		GLUI* getUIRoot() const;
		virtual void createUIControls(CmptMgr& cmptMgr, ShortcutKeyListener* shortcutLsn = NULL) = 0; 

		virtual void onModelEvent(const Event& event) {}

		std::queue<Event>& getEventList();

	protected:
		static const size_t BTN_WIDTH = 10;

	protected:
		GLUI* m_root;

		static std::queue<Event> m_eventList;

	}; // AbstractUICtrlsMgr

	inline GLUI* AbstractUICtrlsMgr::getUIRoot() const
	{
		return m_root;
	}

	inline std::queue<Event>& AbstractUICtrlsMgr::getEventList()
	{
		return m_eventList;
	}
}

#endif // _FEDITOR_ABSTRACT_UI_CTRLS_MGR_H_