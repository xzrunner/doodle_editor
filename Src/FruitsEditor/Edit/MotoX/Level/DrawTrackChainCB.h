#ifndef _FEDITOR_MOTOX_LEVEL_DRAW_TRACK_CHAIN_CB_H_
#define _FEDITOR_MOTOX_LEVEL_DRAW_TRACK_CHAIN_CB_H_
#include "../../EditOperation/AbstractEditOpCB.h"

namespace FEDITOR
{
	class ChainShape;

	namespace MOTOX
	{
		namespace LEVEL
		{
			class TrackChains;

			class DrawTrackChainCB : public AbstractEditOpCB
			{
			public:
				DrawTrackChainCB(TrackChains& trackChains);
				virtual ~DrawTrackChainCB();

				virtual void afterMouseLeftDown(const f2Vec2& pos);
				virtual void afterMouseRightDown(const f2Vec2& pos);
				virtual void afterMouseMove(const f2Vec2& pos);

			private:
				void eraseEmptyShape();

			private:
				TrackChains& m_trackChains;
				ChainShape *m_staticShape, *m_dynamicShape;

			}; // DrawTrackChainCB
		}
	}
}

#endif // _FEDITOR_MOTOX_LEVEL_DRAW_TRACK_CHAIN_CB_H_