#ifndef _EASY_BUILDER_ACTORS_LIST_H_
#define _EASY_BUILDER_ACTORS_LIST_H_

#include <wxGUI/wxGUI.h>

namespace ebuilder
{
	class ActorsPage;

	class ActorsList : public wxgui::LibraryList
	{
	public:
		ActorsList(wxWindow* parent);

		//
		// ISerializable interface
		//
		virtual void loadFromTextFile(std::ifstream& fin);
		virtual void storeToTextFile(std::ofstream& fout) const;

		virtual void onListSelected(wxCommandEvent& event);

	}; // ActorsList
}

#endif // _EASY_BUILDER_ACTORS_LIST_H_