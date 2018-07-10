#ifndef _FEDITOR_COMPOSE_IMG_VIEW_H_
#define _FEDITOR_COMPOSE_IMG_VIEW_H_
#include "Edit/AbstractView.h"

namespace FEDITOR
{
	namespace COMPOSE_IMG
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

#endif // _FEDITOR_COMPOSE_IMG_VIEW_H_