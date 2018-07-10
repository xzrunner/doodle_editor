#ifndef _FEDITOR_BASKETBALL_VIEW_H_
#define _FEDITOR_BASKETBALL_VIEW_H_
#include "../../AbstractView.h"

namespace FEDITOR
{
	namespace BASKETBALL
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

#endif // _FEDITOR_BASKETBALL_VIEW_H_