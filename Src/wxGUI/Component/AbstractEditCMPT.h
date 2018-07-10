#ifndef _WX_GUI_ABSTRACT_EDIT_CMPT_H_
#define _WX_GUI_ABSTRACT_EDIT_CMPT_H_

#include <wx/wx.h>
#include <vector>

namespace wxgui
{
	class EditPanel;
	class AbstractEditOP;

	class AbstractEditCMPT : public wxPanel
	{
	public:
		AbstractEditCMPT(wxWindow* parent, const wxString& name, EditPanel* editPanel,
			const wxString& childrenName = wxEmptyString);
		virtual ~AbstractEditCMPT();

		virtual void updateControlValue() {}

	protected:
		virtual wxSizer* initLayout() = 0;

		virtual void show(bool show) {}

		void addChild(AbstractEditCMPT* child) { m_children.push_back(child); }

		wxSizer* initChildrenLayout();

	private:
		void loadEditOP();
		void loadEditOP(AbstractEditCMPT* cmpt);

		void onChangeEditType(wxCommandEvent& event);

	private:
		// wxRadioBox + Spacer
		static const int CMPT_SIZER_INDEX_OFFSET = 2;

	protected:
		EditPanel* m_editPanel;

		AbstractEditOP* m_editOP;

	private:
		wxString m_name;

		wxString m_childrenName;
		std::vector<AbstractEditCMPT*> m_children;
		wxSizer* m_childrenSizer;

	}; // AbstractEditCMPT
}

#endif // _WX_GUI_ABSTRACT_EDIT_CMPT_H_