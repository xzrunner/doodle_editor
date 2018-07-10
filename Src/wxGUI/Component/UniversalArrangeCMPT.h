#ifndef _WX_GUI_UNIVERSAL_ARRANGE_CMPT_H_
#define _WX_GUI_UNIVERSAL_ARRANGE_CMPT_H_

#include "AbstractEditCMPT.h"

#include <Box2D/Box2D.h>
#include <Fruits2D/Fruits2D.h>

namespace wxgui
{
	class MultiSpritesImpl;
	class PropertySettingPanel;

	class UniversalArrangeCMPT : public AbstractEditCMPT
	{
	public:
		UniversalArrangeCMPT(wxWindow* parent, const wxString& name,
			EditPanel* editPanel, MultiSpritesImpl* spritesImpl,
			PropertySettingPanel* propertyPanel);

		virtual void updateControlValue();

		void addPhysicsEditOP(b2World* world, b2Body* ground);

	protected:
		virtual wxSizer* initLayout();

	private:
		class GetPhysicsStaticVisitor : public IVisitor
		{
		public:
			enum TYPE
			{
				e_checked,
				e_unchecked,
				e_uncertain
			};

		public:
			GetPhysicsStaticVisitor();
			virtual void visit(IObject* object, bool& bFetchNext);
			TYPE getType() const { return m_type; }

		private:
			TYPE m_type;	// 0 all open, 1 all close, 2 uncertain

		}; // GetPhysicsStaticVisitor

		class SetPhysicsStaticVisitor : public IVisitor
		{
		public:
			SetPhysicsStaticVisitor(bool bChecked);
			virtual void visit(IObject* object, bool& bFetchNext);

		private:
			bool m_bChecked;

		}; // SetPhysicsStaticVisitor

	private:
		void onChangeStaticType(wxCommandEvent& event);

	private:
		MultiSpritesImpl* m_spritesImpl;

		wxCheckBox* m_physicsStaticCtrl;
		
	}; // UniversalArrangeCMPT
}

#endif // _WX_GUI_UNIVERSAL_ARRANGE_CMPT_H_