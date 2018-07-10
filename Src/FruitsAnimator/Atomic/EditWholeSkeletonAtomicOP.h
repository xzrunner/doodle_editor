#ifndef _FRUITS_ANIMATOR_EDIT_WHOLE_SKELETON_ATOMIC_OP_H_
#define _FRUITS_ANIMATOR_EDIT_WHOLE_SKELETON_ATOMIC_OP_H_

#include "Edit/EditWholeSkeletonOP.h"

namespace FRUITS_ANIMATOR
{
	namespace edit_whole_skeleton
	{
		class RotateBoneAOP : public wxgui::AbstractAtomicOP
		{
		public:
			RotateBoneAOP(wxgui::EditPanel* editPanel, 
				WholeSkeleton::Sprite* selected, float delta);

			virtual void undo();
			virtual void redo();

		private:
			wxgui::EditPanel* m_editPanel;

			WholeSkeleton::Sprite* m_selected;
			float m_delta;

		}; // RotateBoneAOP
	}
}

#endif // _FRUITS_ANIMATOR_EDIT_WHOLE_SKELETON_ATOMIC_OP_H_