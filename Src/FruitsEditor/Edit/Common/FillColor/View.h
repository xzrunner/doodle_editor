#ifndef _FEDITOR_FILL_COLOR_VIEW_H_
#define _FEDITOR_FILL_COLOR_VIEW_H_
#include "Edit/AbstractView.h"

namespace FEDITOR
{
	namespace FILL_COLOR
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

#endif // _FEDITOR_FILL_COLOR_VIEW_H_