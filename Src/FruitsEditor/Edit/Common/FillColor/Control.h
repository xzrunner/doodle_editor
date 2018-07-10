#ifndef _FEDITOR_FILL_COLOR_CONTROL_H_
#define _FEDITOR_FILL_COLOR_CONTROL_H_
#include "Edit/AbstractControl.h"

namespace FEDITOR
{
	class LayersMgrCmpt;
	class DrawPolylineCmpt;
	class SetColorCmpt;

	namespace FILL_COLOR
	{
		class Control : public AbstractControl
		{
		public:
			Control();
			virtual ~Control();

			static AbstractControl* Create()
			{
				return new Control;
			}

		protected:
			virtual void onMouseRightDown(int x, int y);

			virtual void createEditCmpt();

			virtual void handleStep();
			virtual void handleUIEvent();

		private:
			void setSelectSpritesOp();

			std::vector<f2Vec2> getSelectedCtlpos() const;

		private:
			LayersMgrCmpt* m_layersMgrCmpt;
			DrawPolylineCmpt* m_drawCmpt;
			SetColorCmpt* m_setColorCmpt;

//			Sprite* m_selected;

		}; // Control
	}
}

#endif // _FEDITOR_FILL_COLOR_CONTROL_H_