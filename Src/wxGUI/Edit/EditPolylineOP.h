#ifndef _WX_GUI_EDIT_POLYLINE_OP_H_
#define _WX_GUI_EDIT_POLYLINE_OP_H_

#include "View/MultiShapesImpl.h"
#include "Component/DrawPolylineCMPT.h"
#include "Dataset/ChainShape.h"

namespace wxgui
{
	class EditPanel;
	class MultiShapesImpl;
	class DrawPolylineCMPT;
	class ChainShape;
	class SelectShapesOP;

	template <typename TBase, typename TSelected, typename TCMPT>
	class EditPolylineOP : public TBase
	{
	public:
		EditPolylineOP(EditPanel* editPanel, 
			MultiShapesImpl* shapesImpl, TCMPT* cmpt);
		virtual ~EditPolylineOP();

		virtual bool onKeyDown(int keyCode);
		virtual bool onMouseLeftDown(int x, int y);
		virtual bool onMouseLeftUp(int x, int y);
		virtual bool onMouseRightDown(int x, int y);
		virtual bool onMouseMove(int x, int y);
		virtual bool onMouseDrag(int x, int y);

		virtual bool onDraw() const;
		virtual bool clear();

	private:
		struct NodeAddr
		{
			ChainShape* chain;
			f2Vec2 pos;

			NodeAddr() : chain(NULL) {}
		};

		class NodeCapture
		{
		public:
			NodeCapture(MultiShapesImpl* shapesImpl, int tol);

			void captureEditable(const f2Vec2& pos, NodeAddr& result);
			void captureSelectable(const f2Vec2& pos, NodeAddr& result);

		private:
			class QueryChainVisitor : public IVisitor
			{
			public:
				QueryChainVisitor(const f2Vec2& pos, float tolerance, NodeAddr& result);

				virtual void visit(IObject* object, bool& bFetchNext);

			private:
				const f2Vec2& m_pos;
				float m_tolerance;

				f2AABB m_aabb;
				NodeAddr& m_result;

			}; // SetTexCoordsVisitor

		private:
			MultiShapesImpl* m_shapesImpl;
			int m_tol;

		}; // NodeCapture

		class InterruptChainVisitor : public IVisitor
		{
		public:
			InterruptChainVisitor(const f2Vec2& pos, int tol);

			virtual void visit(IObject* object, bool& bFetchNext);

			ChainShape* getInterruptedChain() { return m_chain; }

		private:
			const f2Vec2& m_pos;
			int m_tol;
			ChainShape* m_chain;

		}; // InterruptChainVisitor

	private:
		static const int DRAG_SELECT_TOL = 5;

	private:
		MultiShapesImpl* m_shapesImpl;

		TCMPT* m_cmpt;
//		NodeAddr m_captured;
		NodeAddr m_capturedEditable, m_captureSelectable;

	protected:
		TSelected* m_selectOP;
	private:
		f2Vec2 m_lastLeftDownPos;
		bool m_bSelectOpen;

	}; // EditPolylineOP
}

#include "EditPolylineOP.cpp"

#endif // _WX_GUI_EDIT_POLYLINE_OP_H_