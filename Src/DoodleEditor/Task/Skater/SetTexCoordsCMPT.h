#ifndef _DEDITOR_SKATER_SET_TEX_COORDS_CMPT_H_
#define _DEDITOR_SKATER_SET_TEX_COORDS_CMPT_H_

#include <wxGUI/wxGUI.h>

namespace deditor
{
	namespace skater
	{
		class StagePanel;

		class SetTexCoordsCMPT : public wxgui::AbstractEditCMPT
		{
		public:
			SetTexCoordsCMPT(wxWindow* parent, const wxString& name, 
				StagePanel* editPanel, wxgui::PropertySettingPanel* propertyPanel);

			virtual void updateControlValue();

		protected:
			virtual wxSizer* initLayout();

		private:
			void onChangeTexCoords(wxScrollEvent& event);

		private:
			struct TexCoordsCtrl
			{
				wxSlider *leftSlider, *rightSlider, *downSlider, *upSlider;

				void disable();
				void enable();
				void setValue(float* val);
			};

			class FetchFirstSelectedVisitor : public IVisitor
			{
			public:
				FetchFirstSelectedVisitor(wxgui::ISprite** pFirst);
				virtual void visit(IObject* object, bool& bFetchNext);

			private:
				wxgui::ISprite** m_pFirst;

			}; // FetchFirstSelectedVisitor

			class SetTexCoordsVisitor : public IVisitor
			{
			public:
				SetTexCoordsVisitor(const TexCoordsCtrl& texCoordsCtrl);
				virtual void visit(IObject* object, bool& bFetchNext);

			private:
				float m_coords[4];

			}; // SetTexCoordsVisitor

		private:
			TexCoordsCtrl m_texCoordsCtrl;

		}; // SetTexCoordsCMPT
	}
}

#endif // _DEDITOR_SKATER_SET_TEX_COORDS_CMPT_H_