#ifndef _EASY_BUILDER_SCENES_LIST_H_
#define _EASY_BUILDER_SCENES_LIST_H_

#include <wxGUI/wxGUI.h>

namespace ebuilder
{
	class ScenesPage;

	class ScenesList : public wxgui::LibraryList
	{
	public:
		ScenesList(ScenesPage* scenesPage);

		//
		// ISerializable interface
		//
		virtual void loadFromTextFile(std::ifstream& fin);
		virtual void storeToTextFile(std::ofstream& fout) const;

		virtual void onListSelected(wxCommandEvent& event);

	private:
		ScenesPage* m_scenesPage;

	}; // ScenesList
}

#endif // _EASY_BUILDER_SCENES_LIST_H_