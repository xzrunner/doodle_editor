#ifndef _DEDITOR_MOTOX_OBSTACLE_BRIDGE_OP_H_
#define _DEDITOR_MOTOX_OBSTACLE_BRIDGE_OP_H_

#include <wxGUI/wxGUI.h>

namespace deditor
{
	namespace motox
	{
		class StagePanel;
		class ObstacleBridgeCMPT;
		class BridgeData;

		class ObstacleBridgeOP : public wxgui::ZoomViewOP
		{
		public:
			ObstacleBridgeOP(StagePanel* stagePanel, ObstacleBridgeCMPT* cmpt);
			virtual ~ObstacleBridgeOP();

			virtual bool onMouseLeftDown(int x, int y);
			virtual bool onMouseLeftUp(int x, int y);
			virtual bool onMouseDrag(int x, int y);

			virtual bool onDraw() const;
			virtual bool clear();

		private:
			void createBridge();

			void queryByPos(const f2Vec2& pos);

		private:
			struct Bridge
			{
				f2Vec2 start, end;

				BridgeData* bridgeMesh;

			}; // Bridge

		private:
			static const int END_POS_RADIUS = 10;

		private:
			StagePanel* m_stagePanel;

			ObstacleBridgeCMPT* m_cmpt;

			f2Vec2 m_beginPos, m_endPos;

			std::vector<Bridge*> m_bridges;
			Bridge* m_selected;
			bool m_bSelectStart;

		}; // ObstacleBridgeOP
	}
}

#endif // _DEDITOR_MOTOX_OBSTACLE_BRIDGE_OP_H_