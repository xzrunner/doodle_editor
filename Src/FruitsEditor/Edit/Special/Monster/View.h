#ifndef _FEDITOR_MONSTER_VIEW_H_
#define _FEDITOR_MONSTER_VIEW_H_
#include "Edit/AbstractView.h"

namespace FEDITOR
{
	namespace MONSTER
	{
		class View : public AbstractView
		{
		public:
			View(float scale = 1.0f);

		protected:
			virtual void onDraw(const LayersMgr& layers) const;
			virtual void onUIEvent(const Event& event);

		}; // View
	}
}

#endif // _FEDITOR_MONSTER_VIEW_H_