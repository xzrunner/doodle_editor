#ifndef _FEDITOR_GUIDELINES_LONG_CMPT_H_
#define _FEDITOR_GUIDELINES_LONG_CMPT_H_
#include "AbstractCmpt.h"
#include "../Utility.h"

class GLUI_Spinner;

namespace FEDITOR
{
	class Sprite;
	class LayersMgr;

	class GuidelinesLongCmpt : public AbstractCmpt
	{
	public:
		GuidelinesLongCmpt(LayersMgr& layers, CmptMgr& cmptMgr, int baseLength = 100);

		virtual void createUIControls(GLUI_Node* parent, ShortcutKeyListener* shortcutLsn);
		virtual void handleUIEvent();

	private:
		void smallLayoutUI(GLUI_Node* parent);
		void largeLayoutUI(GLUI_Node* parent);

		void changeGuidelines();

		void createXGuidelines();
		void createXYGuidelines();
		void createCoordinateAxes();

	private:
		static const int WIDTH_TIMES = 100;

	private:
		enum
		{
			e_SetType,
			e_SetGridSize,
			e_SetDisplayAxes
		};

		static void callback(int id);

	private:
		Sprite* m_sprite;

		int m_type;
			// 0 Null
			// 1 only x
			// 2 xy grids

		GLUI_Spinner *m_setGridXSize, *m_setGridYSize;
		int m_gridXSize, m_gridYSize;

		int m_displayAxes;

		static std::queue<Event> m_eventList;

	}; // GuidelinesLongCmpt
}

#endif // _FEDITOR_GUIDELINES_LONG_CMPT_H_