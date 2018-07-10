#ifndef _GAME_FRUITS_REGULAR_COLLAPSIBLE_PANE_H_
#define _GAME_FRUITS_REGULAR_COLLAPSIBLE_PANE_H_
#include <wx/wx.h>
#include <wx/collpane.h>

namespace GAME_FRUITS
{
	namespace REGULAR
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

		inline CollapsiblePane::CollapsiblePane(wxWindow* parent, const wxString& name)
			: wxCollapsiblePane(parent, wxID_ANY, name)
		{
			m_parent = parent;
		}

		inline void CollapsiblePane::Collapse(bool collapse/* = true*/)
		{
			wxCollapsiblePane::Collapse(collapse);
			refresh();
		}

		inline void CollapsiblePane::refresh()
		{
			m_parent->Layout();
			m_parent->Refresh();
			if (m_parent->GetParent())
			{
				CollapsiblePane* grand = dynamic_cast<CollapsiblePane*>(m_parent->GetParent());
				if (grand) grand->refresh();
			}
		}
	}
}

#endif // _GAME_FRUITS_REGULAR_COLLAPSIBLE_PANE_H_