#ifndef _FEDITOR_GUIDELINES_CMPT_H_
#define _FEDITOR_GUIDELINES_CMPT_H_
#include "AbstractCmpt.h"
#include "../Utility.h"

class GLUI_Spinner;

namespace FEDITOR
{
	class Sprite;
	class LayersMgr;

	class GuidelinesCmpt : public AbstractCmpt
	{
	public:
		GuidelinesCmpt(LayersMgr& layers, CmptMgr& cmptMgr);

		virtual void createUIControls(GLUI_Node* parent, ShortcutKeyListener* shortcutLsn);
		virtual void handleUIEvent();

	private:
		void smallLayoutUI(GLUI_Node* parent);
		void largeLayoutUI(GLUI_Node* parent);

		void changeGuidelines();

		void createPolygonLines();
		void createCrossLines();
		void createGridLines();

	private:
		static const int WIDTH_TIMES = 100;

	private:
		enum
		{
			e_SetType,
			e_SetGridSize
		};

		static void callback(int id);

	private:
		Sprite* m_sprite;

		int m_type;
			// 0 Null
			// 1 Polygon
			// 2 Cross
			// 3 Grid

		GLUI_Spinner* m_setGridSize;
		int m_gridSize;

		static std::queue<Event> m_eventList;

	}; // GuidelinesCmpt
}

#endif // _FEDITOR_GUIDELINES_CMPT_H_