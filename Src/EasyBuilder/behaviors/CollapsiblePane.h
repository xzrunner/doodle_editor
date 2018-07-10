#ifndef _EASY_BUILDER_COLLAPSIBLE_PANEL_H_
#define _EASY_BUILDER_COLLAPSIBLE_PANEL_H_

#include <wx/wx.h>
#include <wx/collpane.h>

namespace ebuilder
{
	class CollapsiblePane : public wxCollapsiblePane
	{
	public:
		CollapsiblePane(wxWindow* parent, const wxString& name);

		virtual void Collapse(bool collapse = true);

	private:
		void refresh();

	protected:
		wxWindow* m_parent;

	}; // CollapsiblePane
}

#endif // _EASY_BUILDER_COLLAPSIBLE_PANEL_H_