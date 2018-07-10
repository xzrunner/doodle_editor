#ifndef _FRUITS_ANIMATOR_SKELETON_EDIT_DIALOG_H_
#define _FRUITS_ANIMATOR_SKELETON_EDIT_DIALOG_H_

#include <wx/wx.h>

namespace FRUITS_ANIMATOR
{
	class WholeSkeleton;
	class LibraryPanel;
	class SkeletonEditPanel;

	class SkeletonEditDialog : public wxDialog
	{
	public:
		SkeletonEditDialog(wxWindow* parent, WholeSkeleton* skeleton, 
			LibraryPanel* library);
		~SkeletonEditDialog();

	private:
		void onSize(wxSizeEvent& event);

		void initLayout(LibraryPanel* library);

		void onLayerChange(wxCommandEvent& event);

	private:
		WholeSkeleton* m_skeleton;
		SkeletonEditPanel* m_editPanel;

		DECLARE_EVENT_TABLE()

	}; // SkeletonEditDialog
}

#endif // _FRUITS_ANIMATOR_SKELETON_EDIT_DIALOG_H_