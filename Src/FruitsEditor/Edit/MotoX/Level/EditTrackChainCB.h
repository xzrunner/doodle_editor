#ifndef _FEDITOR_MOTOX_LEVEL_EDIT_TRACK_CHAIN_CB_H_
#define _FEDITOR_MOTOX_LEVEL_EDIT_TRACK_CHAIN_CB_H_
#include "../../EditOperation/AbstractEditOpCB.h"

namespace FEDITOR
{
	namespace MOTOX
	{
		namespace LEVEL
		{
			class TrackChains;

			class EditTrackChainCB : public AbstractEditOpCB
			{
			public:
				EditTrackChainCB(TrackChains& trackChains);
				virtual ~EditTrackChainCB();

				virtual void afterKeyboard(unsigned char key);
				virtual void afterMouseLeftUp(const f2Vec2& pos);
				virtual void afterMouseRightUp(const f2Vec2& pos);

			private:
				TrackChains& m_trackChains;

			}; // EditTrackChainCB
		}
	}
}

#endif // _FEDITOR_MOTOX_LEVEL_EDIT_TRACK_CHAIN_CB_H_