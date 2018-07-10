#ifndef _DEDITOR_MOTOX_TRACK_CHAIN_EDIT_CMPT_H_
#define _DEDITOR_MOTOX_TRACK_CHAIN_EDIT_CMPT_H_

#include <wxGUI/wxGUI.h>

namespace deditor
{
	namespace motox
	{
		class StagePanel;

		class TrackChainEditCMPT : public wxgui::AbstractEditCMPT
		{
		public:
			TrackChainEditCMPT(wxWindow* parent, const wxString& name,
				StagePanel* editPanel);

		protected:
			virtual wxSizer* initLayout();

		private:
			void onSetScale(wxCommandEvent& event);
			void onSetOffset(wxSpinEvent& event);

		private:
			class ScaleVisitor : public IVisitor
			{
			public:
				ScaleVisitor(float scale) : m_scale(scale) {}
				virtual void visit(IObject* object, bool& bFetchNext);

			private:
				float m_scale;

			}; // ScaleVisitor

			class TranslationVisitor : public IVisitor
			{
			public:
				TranslationVisitor(const f2Vec2& offset) : m_offset(offset) {}
				virtual void visit(IObject* object, bool& bFetchNext);

			private:
				f2Vec2 m_offset;

			}; // TranslationVisitor

		private:
			StagePanel* m_editPanel;

			wxSpinCtrl *m_xOffset, *m_yOffset;

		}; // TrackChainEditCMPT
	}
}

#endif // _DEDITOR_MOTOX_TRACK_CHAIN_EDIT_CMPT_H_