#ifndef _EASY_BUILDER_BEHAVIORS_PAGE_H_
#define _EASY_BUILDER_BEHAVIORS_PAGE_H_

#include <wxGUI/wxGUI.h>

namespace ebuilder
{
	class BehaviorsPage : public wxgui::ILibraryPage
	{
	public:
		BehaviorsPage(wxWindow* parent);

		virtual bool isHandleSymbol(wxgui::ISymbol* symbol) const;

		virtual void clear();

	protected:
		virtual void initLayout(bool draggable = true);

		virtual void onAddPress(wxCommandEvent& event);

	private:
		void initBehaviors();

	}; // BehaviorsPage
}

#endif // _EASY_BUILDER_BEHAVIORS_PAGE_H_