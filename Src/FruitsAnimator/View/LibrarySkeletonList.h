#ifndef _FRUITS_ANIMATOR_LIBRARY_SKELETON_LIST_H_
#define _FRUITS_ANIMATOR_LIBRARY_SKELETON_LIST_H_

#include "Dataset/WholeSkeleton.h"

#include <wxGUI/wxGUI.h>

namespace FRUITS_ANIMATOR
{
	class LibraryPanel;
	class StagePanel;
	class WholeSkeleton;

	class LibrarySkeletonList : public wxgui::VerticalImageList, public ISerializable
	{
	public:
		LibrarySkeletonList(wxWindow* parent, LibraryPanel* library);
	
		//
		// ISerializable interface
		//
		virtual void loadFromTextFile(std::ifstream& fin);
		virtual void storeToTextFile(std::ofstream& fout) const;

		WholeSkeleton* getSkeleton(int index) const;
		int getIndex(WholeSkeleton* skeleton) const;

		void setStagePanel(StagePanel* stagePanel);

	protected:
		void onListDoubleClicked(wxCommandEvent& event);

	private:
		void loadDataFromSymbolList(std::vector<WholeSkeleton::Node*>& nodes,
			std::vector<WholeSkeleton::Body*>& bodies) const;

	private:
		LibraryPanel* m_library;

		StagePanel* m_stagePanel;

	}; // LibrarySkeletonList
}

#endif // _FRUITS_ANIMATOR_LIBRARY_SKELETON_LIST_H_