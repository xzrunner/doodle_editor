#ifndef _FRUITS_ANIMATOR_ADD_PART_SKELETON_JOINT_OP_H_
#define _FRUITS_ANIMATOR_ADD_PART_SKELETON_JOINT_OP_H_

#include "Dataset/PartSkeleton.h"

#include <wxGUI/wxGUI.h>

namespace FRUITS_ANIMATOR
{
	class AddPartSkeletonJointOP : public wxgui::ZoomViewOP
	{
	public:
		AddPartSkeletonJointOP(wxgui::EditPanel* editPanel, PartSkeleton* skeleton);

		virtual bool onMouseLeftDown(int x, int y);
		virtual bool onMouseRightDown(int x, int y);
		virtual bool onMouseMove(int x, int y);

		virtual bool onDraw() const;
		virtual bool clear();

	private:
		PartSkeleton* m_skeleton;

		f2Vec2 m_lastPos;

	}; // AddPartSkeletonJointOP
}

#endif // _FRUITS_ANIMATOR_ADD_PART_SKELETON_JOINT_OP_H_