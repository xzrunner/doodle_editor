#ifndef _FRUITS_ANIMATOR_LIBRARY_SKELETON_PAGE_H_
#define _FRUITS_ANIMATOR_LIBRARY_SKELETON_PAGE_H_

#include <wxGUI/wxGUI.h>

namespace FRUITS_ANIMATOR
{
	class StagePanel;
	class LibraryPanel;
	class LibrarySkeletonList;
	class WholeSkeleton;

	class LibrarySkeletonPage : public wxgui::ILibraryPage
	{
	public:
		LibrarySkeletonPage(wxWindow* parent, LibraryPanel* library);

		//
		// ISerializable interface
		//
		virtual void loadFromTextFile(std::ifstream& fin);
		virtual void storeToTextFile(std::ofstream& fout) const;

		virtual void traverse(IVisitor& visitor) const;

		WholeSkeleton* getSkeleton(int index) const;
		int getIndex(WholeSkeleton* skeleton) const;

		void setStagePanel(StagePanel* stagePanel);

		void clear();

 	protected:
 		virtual void onAddPress(wxCommandEvent& event);
 		virtual void onDelPress(wxCommandEvent& event);

	private:
		StagePanel* m_stagePanel;
		LibraryPanel* m_library;
		LibrarySkeletonList* m_skeletonList;

	}; // LibrarySkeletonPage
}

#endif // _FRUITS_ANIMATOR_LIBRARY_SKELETON_PAGE_H_