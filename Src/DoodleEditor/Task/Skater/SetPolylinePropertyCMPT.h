#ifndef _DEDITOR_SKATER_SET_POLYLINE_PROPERTY_CMPT_H_
#define _DEDITOR_SKATER_SET_POLYLINE_PROPERTY_CMPT_H_

#include <wxGUI/wxGUI.h>

namespace deditor
{
	namespace skater
	{
		class StagePanel;

		class SetPolylinePropertyCMPT : public wxgui::AbstractEditCMPT
		{
		public:
			SetPolylinePropertyCMPT(wxWindow* parent, const wxString& name,
				StagePanel* editPanel);

			virtual void updateControlValue();

		protected:
			virtual wxSizer* initLayout();

		private:
			void onChangeCloseType(wxCommandEvent& event);
			void onChangeID(wxCommandEvent& event);

		private:
			class GetChainCloseVisitor : public IVisitor
			{
			public:
				enum TYPE
				{
					e_open,
					e_close,
					e_uncertain
				};

			public:
				GetChainCloseVisitor();
				virtual void visit(IObject* object, bool& bFetchNext);
				TYPE getType() const { return m_type; }

			private:
				TYPE m_type;	// 0 all open, 1 all close, 2 uncertain

			}; // GetChainCloseVisitor

			class GetChainIDVisitor : public IVisitor
			{
			public:
				GetChainIDVisitor();
				virtual void visit(IObject* object, bool& bFetchNext);
				int getID() const { return m_id; }

			private:
				int m_id;	// FLOAT_MAX: don't have a same value

			}; // GetChainIDVisitor

			class SetChainCloseVisitor : public IVisitor
			{
			public:
				SetChainCloseVisitor(bool bClose);
				virtual void visit(IObject* object, bool& bFetchNext);

			private:
				bool m_bClose;

			}; // SetChainCloseVisitor

			class SetChainIDVisitor : public IVisitor
			{
			public:
				SetChainIDVisitor(int id);
				virtual void visit(IObject* object, bool& bFetchNext);

			private:
				int m_id;

			}; // SetChainIDVisitor

		private:
			wxCheckBox* m_closeCtrl;
			wxTextCtrl* m_idCtrl;

		}; // SetPolylinePropertyCMPT
	}
}

#endif // _DEDITOR_SKATER_SET_POLYLINE_PROPERTY_CMPT_H_