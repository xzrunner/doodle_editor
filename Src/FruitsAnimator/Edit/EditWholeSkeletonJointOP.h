#ifndef _FRUITS_ANIMATOR_EDIT_WHOLE_SKELETON_JOINT_OP_H_
#define _FRUITS_ANIMATOR_EDIT_WHOLE_SKELETON_JOINT_OP_H_

#include "Dataset/WholeSkeleton.h"

#include <wxGUI/wxGUI.h>

namespace FRUITS_ANIMATOR
{
	class EditWholeSkeletonJointOP : public wxgui::ZoomViewOP
	{
	public:
		EditWholeSkeletonJointOP(wxgui::EditPanel* editPanel, WholeSkeleton::Body* body);

		virtual bool onMouseLeftDown(int x, int y);
		virtual bool onMouseLeftUp(int x, int y);
		virtual bool onMouseRightDown(int x, int y);
		virtual bool onMouseDrag(int x, int y);

		virtual bool onDraw() const;
		virtual bool clear();

	private:
		WholeSkeleton::Body* m_body;

		WholeSkeleton::Node* m_selected;

	}; // EditWholeSkeletonJointOP
}

#endif // _FRUITS_ANIMATOR_EDIT_WHOLE_SKELETON_JOINT_OP_H_