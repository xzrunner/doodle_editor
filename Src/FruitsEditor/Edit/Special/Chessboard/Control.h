#ifndef _FEDITOR_CHESSBOARD_CONTROL_H_
#define _FEDITOR_CHESSBOARD_CONTROL_H_
#include "Edit/AbstractControl.h"

namespace FEDITOR
{
	namespace CHESSBOARD
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
			void openTile(const std::string& filename);
			void setArrangeSpriteOp();

		}; // Control
	}
}

#endif // _FEDITOR_CHESSBOARD_CONTROL_H_