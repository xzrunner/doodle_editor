#ifndef _FEDITOR_SKATER_VIEW_H_
#define _FEDITOR_SKATER_VIEW_H_
#include "Edit/AbstractView.h"

namespace FEDITOR
{
	namespace SKATER
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

#endif // _FEDITOR_SKATER_VIEW_H_