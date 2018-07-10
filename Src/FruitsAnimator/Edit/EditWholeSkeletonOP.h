#ifndef _FRUITS_ANIMATOR_EDIT_WHOLE_SKELETON_OP_H_
#define _FRUITS_ANIMATOR_EDIT_WHOLE_SKELETON_OP_H_

#include "Dataset/WholeSkeleton.h"

namespace FRUITS_ANIMATOR
{
	namespace edit_whole_skeleton { class RotateBoneAOP; }

	class EditWholeSkeletonOP : public wxgui::ZoomViewOP
	{
	public:
		EditWholeSkeletonOP(wxgui::EditPanel* editPanel, WholeSkeleton* skeleton);

		virtual bool onMouseLeftDown(int x, int y);
		virtual bool onMouseLeftUp(int x, int y);
		virtual bool onMouseDrag(int x, int y);

		//virtual bool onDraw() const;
		virtual bool clear();

	private:
		WholeSkeleton* m_skeleton;

		WholeSkeleton::Sprite* m_selected;
		f2Vec2 m_lastPos;

		f2Vec2 m_firstPos;

		friend class edit_whole_skeleton::RotateBoneAOP;

	}; // EditWholeSkeletonOP
}

#endif // _FRUITS_ANIMATOR_EDIT_WHOLE_SKELETON_OP_H_