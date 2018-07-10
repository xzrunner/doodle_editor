#ifndef _FRUITS_ANIMATOR_EDIT_SPRITE_PART_SKELETON_OP_H_
#define _FRUITS_ANIMATOR_EDIT_SPRITE_PART_SKELETON_OP_H_

#include "Dataset/PartSkeleton.h"

#include <wxGUI/wxGUI.h>

namespace FRUITS_ANIMATOR
{
	class EditSpritePartSkeletonOP : public wxgui::ZoomViewOP
	{
	public:
		EditSpritePartSkeletonOP(wxgui::EditPanel* editPanel, PartSkeleton* skeleton);
		
		virtual bool onMouseLeftDown(int x, int y);
		virtual bool onMouseLeftUp(int x, int y);
		virtual bool onMouseDrag(int x, int y);

		virtual bool onDraw() const;
		virtual bool clear();

	private:
		PartSkeleton* m_skeleton;

		PartSkeleton::Joint* m_selected;

	}; // EditSpritePartSkeletonOP
}

#endif // _FRUITS_ANIMATOR_EDIT_SPRITE_PART_SKELETON_OP_H_