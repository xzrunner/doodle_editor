#ifndef _FEDITOR_COORDINATE_AXES_CMPT_H_
#define _FEDITOR_COORDINATE_AXES_CMPT_H_
#include "AbstractCmpt.h"
#include "../Utility.h"

namespace FEDITOR
{
	class ChainShape;
	class Sprite;
	class LayersMgr;

	class CoordinateAxesCmpt : public AbstractCmpt
	{
	public:
		CoordinateAxesCmpt(LayersMgr& layers, CmptMgr& cmptMgr);

		virtual void createUIControls(GLUI_Node* parent, ShortcutKeyListener* shortcutLsn);
		virtual void handleUIEvent();

		f2Vec2 transToCurrCoordinate(const f2Vec2& pos) const;

	private:
		void smallLayoutUI(GLUI_Node* parent);
		void largeLayoutUI(GLUI_Node* parent);

		void changeCoordinateAxes();
		void changeDisplay();

		void createCenterLines();
		void createLeftTopLines();
		void createLeftBottomLines();

	private:
		enum
		{
			e_SetType,
			e_SetDisplay
		};

		static void callback(int id);

	private:
		Sprite* m_sprite;

		int m_type;
			// 0 Center
			// 1 LeftTop
			// 2 LeftBottom

		int m_flagDisplay;

		static std::queue<Event> m_eventList;

	}; // CoordinateAxesCmpt
}

#endif // _FEDITOR_COORDINATE_AXES_CMPT_H_