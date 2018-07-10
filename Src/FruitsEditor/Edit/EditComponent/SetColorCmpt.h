#ifndef _FEDITOR_SET_COLOR_CMPT_H_
#define _FEDITOR_SET_COLOR_CMPT_H_
#include "AbstractCmpt.h"
#include "../Utility.h"

namespace FEDITOR
{
	class SetColorCmpt : public AbstractCmpt
	{
	public:
		SetColorCmpt(CmptMgr& cmptMgr, f2Colorf& color);

		virtual void createUIControls(GLUI_Node* parent, ShortcutKeyListener* shortcutLsn);
		virtual void handleUIEvent();

	private:
		void smallLayoutUI(GLUI_Node* parent);
		void largeLayoutUI(GLUI_Node* parent);

	private:
		enum
		{
			e_SetColor
		};

		static void callback(int id);

	private:
		f2Colorf& m_color;

		int m_r, m_g, m_b, m_a;
		
		static std::queue<Event> m_eventList;

	}; // SetColorCmpt
}

#endif // _FEDITOR_SET_COLOR_CMPT_H_