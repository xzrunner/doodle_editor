#ifndef _DEDITOR_COMBINATION_SHAPE_EDIT_OP_H_
#define _DEDITOR_COMBINATION_SHAPE_EDIT_OP_H_

#include <wxGUI/wxGUI.h>

namespace deditor
{
	namespace combination
	{
		class StagePanel;
		class ShapeEditCMPT;

		class ShapeEditOP : public wxgui::EditPolylineOP<
			wxgui::DrawPolygonEdgeOP, 
			wxgui::SelectShapesOP,
			ShapeEditCMPT>
		{
		public:
			ShapeEditOP(StagePanel* editPanel, ShapeEditCMPT* cmpt);

		//	virtual bool onMouseLeftDown(int x, int y);

		//	virtual bool onDraw() const;
		//	virtual bool clear();

		//private:
		//	void buildBorder(const f2Vec2& pos);	
		//	void buildLoops(int width, int height);

		//	bool createLoopByExtend(std::vector<bool>& visited, std::vector<f2Vec2>& loop, f2Vec2& prev, 
		//		const f2Vec2& next, int width, int height) const;
		//	void simplifyBoundaries();

		//private:
		//	ShapeEditCMPT* m_cmpt;

		//	std::vector<f2Vec2> m_border;
		//	std::vector<std::vector<f2Vec2> > m_loopsRaw;
		//	std::vector<std::vector<f2Vec2> > m_loopsSimplified;

		}; // ShapeEditOP
	}
}

#endif // _DEDITOR_COMBINATION_SHAPE_EDIT_OP_H_