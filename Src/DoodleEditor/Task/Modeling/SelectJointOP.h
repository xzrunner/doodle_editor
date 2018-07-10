#ifndef _DEDITOR_MODELING_SELECT_JOINT_OP_H_
#define _DEDITOR_MODELING_SELECT_JOINT_OP_H_

#include "SelectBodyOP.h"

namespace deditor
{
	namespace modeling
	{
		class StagePanel;
		class JointData;

		class SelectJointOP : public SelectBodyOP
		{
		public:
			SelectJointOP(wxgui::EditPanel* editPanel, 
				wxgui::MultiSpritesImpl* spritesImpl, 
				wxgui::PropertySettingPanel* propertyPanel, 
				wxgui::AbstractEditCMPT* callback = NULL);

			virtual bool onKeyDown(int keyCode);
			virtual bool onMouseLeftDown(int x, int y);
			virtual bool onMouseLeftUp(int x, int y);
			virtual bool onMouseMove(int x, int y);
			virtual bool onMouseDrag(int x, int y);

			virtual bool onDraw() const;
			virtual bool clear();

			virtual wxgui::IPropertySetting* createPropertySetting(wxgui::ISprite* sprite) const;

		private:
			class DrawSelectedVisitor : public IVisitor
			{
			public:
				virtual void visit(IObject* object, bool& bFetchNext);

			}; // DrawSelectedVisitor

		private:
			JointData* m_selected;
			JointData* m_mouseOn;

		}; // SelectJointOP
	}
}

#endif // _DEDITOR_MODELING_SELECT_JOINT_OP_H_