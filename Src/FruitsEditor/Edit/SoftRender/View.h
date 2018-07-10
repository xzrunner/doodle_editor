#ifndef _FEDITOR_SOFT_RENDER_VIEW_H_
#define _FEDITOR_SOFT_RENDER_VIEW_H_
#include "FruitsEditor/Edit/AbstractView.h"

namespace FEDITOR
{
	namespace SOFT_RENDER
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

#endif // _FEDITOR_SOFT_RENDER_VIEW_H_