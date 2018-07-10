#ifndef _EASY_BUILDER_BACKSTAGE_PANEL_H_
#define _EASY_BUILDER_BACKSTAGE_PANEL_H_

#include <wx/wx.h>
#include <wx/dnd.h>

namespace ebuilder
{
	class Actor;

	class BackstagePanel : public wxPanel
	{
	public:
		BackstagePanel(wxWindow* parent);

		void initFromActor(Actor* actor);

		Actor* getActor() {
			return m_actor;
		}

	private:
		void initLayout();

		void initTitle(wxSizer* sizer);
		void initSplitterWindow(wxSizer* sizer);

		void onClearPress(wxCommandEvent& event);

// 		// debug
// 		void onChoiceChanged(wxCommandEvent& event);

	private:
		class DragTarget : public wxTextDropTarget
		{
		public:
			DragTarget(wxWindow* parent);

			virtual bool OnDropText(wxCoord x, wxCoord y, const wxString& data);

		private:
			wxWindow* m_parent;

		}; // DragTarget

	private:
		static const float SASH_GRAVITY_HOR;

	private:
		wxButton* m_btnClear;

		wxScrolledWindow* m_behaviorsPanel;

		Actor* m_actor;

		friend class DragTarget;

	}; // BackstagePanel
}

#endif // _EASY_BUILDER_BACKSTAGE_PANEL_H_