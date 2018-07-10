#ifndef _DEDITOR_MODELING_STAGE_CANVAS_H_
#define _DEDITOR_MODELING_STAGE_CANVAS_H_

#include <wxGUI/wxGUI.h>

namespace deditor
{
	namespace modeling
	{
		class StagePanel;

		class StageCanvas : public wxgui::GLCanvas
		{
		public:
			StageCanvas(StagePanel* editPanel);
			virtual ~StageCanvas();

		protected:
			virtual void onDraw();

		private:
			void drawGuideLines();
			void drawSprites();

			void drawCrossLine() const;
			void drawLines() const;

		private:
			class DrawJointVisitor : public IVisitor
			{
			public:
				virtual void visit(IObject* object, bool& bFetchNext);
			};

		}; // StageCanvas
	}
}

#endif // _DEDITOR_MODELING_STAGE_CANVAS_H_