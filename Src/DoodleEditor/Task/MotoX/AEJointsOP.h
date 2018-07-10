#ifndef _DEDITOR_MOTOX_ACTOR_EDIT_JOINTS_OP_H_
#define _DEDITOR_MOTOX_ACTOR_EDIT_JOINTS_OP_H_

#include <wxGUI/wxGUI.h>

namespace deditor
{
	namespace motox
	{
		class AEEditPanel;
		class AEJointsCMPT;
		class AEJoints;

		class AEJointsOP : public wxgui::ZoomViewOP
		{
		public:
			AEJointsOP(AEEditPanel* editPanel, AEJointsCMPT* cmpt);

			virtual bool onMouseLeftDown(int x, int y);
			virtual bool onMouseDrag(int x, int y);

			virtual bool onDraw() const;

		private:
			void createJoint(int x, int y);

		private:
			AEJointsCMPT* m_cmpt;

			AEJoints& m_joints;

		}; // AEJointsOP
	}
}

#endif // _DEDITOR_MOTOX_ACTOR_EDIT_JOINTS_OP_H_