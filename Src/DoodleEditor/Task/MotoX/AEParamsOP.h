#ifndef _DEDITOR_MOTOX_ACTOR_EDIT_PARAMS_OP_H_
#define _DEDITOR_MOTOX_ACTOR_EDIT_PARAMS_OP_H_

#include <wxGUI/wxGUI.h>

namespace deditor
{
	namespace motox
	{
		class AEEditPanel;
		class AEJoints;

		class AEParamsOP : public wxgui::DragPhysicsOP
		{
		public:
			AEParamsOP(AEEditPanel* editPanel);

			virtual bool onKeyDown(int keyCode);

		private:
			AEJoints& m_joints;

		}; // AEParamsOP
	}
}

#endif // _DEDITOR_MOTOX_ACTOR_EDIT_PARAMS_OP_H_