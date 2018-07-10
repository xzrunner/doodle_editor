#ifndef _DEDITOR_SKATER_STAGE_CANVAS_H_
#define _DEDITOR_SKATER_STAGE_CANVAS_H_

#include <wxGUI/wxGUI.h>

namespace deditor
{
	namespace skater
	{
		class StagePanel;

		class StageCanvas : public wxgui::GLCanvas
		{
		public:
			StageCanvas(StagePanel* parent);

		protected:
			virtual void onDraw();

 		private:
 			class DrawSpriteVisitor : public IVisitor
 			{
 			public:
 				DrawSpriteVisitor();
 				virtual void visit(IObject* object, bool& bFetchNext);
 			}; // DrawSpriteVisitor

			class DrawChainVisitor : public IVisitor
			{
			public:
				DrawChainVisitor();
				virtual ~DrawChainVisitor();
				virtual void visit(IObject* object, bool& bFetchNext);
			}; // DrawChainVisitor

		private:
			void drawGuideLines();

		}; // StageCanvas
	}
}

#endif // _DEDITOR_SKATER_STAGE_CANVAS_H_