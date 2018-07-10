#ifndef _FEDITOR_TEXTURE_MERGE_CONTROL_H_
#define _FEDITOR_TEXTURE_MERGE_CONTROL_H_
#include "Edit/AbstractControl.h"

namespace FEDITOR
{
	namespace TEXTURE_MERGE
	{
		class Control : public AbstractControl
		{
		public:
			Control();
			virtual ~Control();

			static AbstractControl* Create()
			{
				return new Control;
			}

		protected:
			virtual void onMouseRightDown(int x, int y);

			virtual void createEditCmpt();

			virtual void handleStep();
			virtual void handleUIEvent(); 

		private:
			void setArrangeSpriteOp();

		}; // Control
	}
}

#endif // _FEDITOR_TEXTURE_MERGE_CONTROL_H_