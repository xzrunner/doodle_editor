#ifndef _WX_GUI_SELECT_NODES_OP_H_
#define _WX_GUI_SELECT_NODES_OP_H_

#include "DrawRectangleOP.h"

#include "Dataset/SelectionSet.h"

namespace wxgui
{
	class MultiShapesImpl;
	class AbstractEditCMPT;
	class ChainShape;

	class SelectNodesOP : public DrawRectangleOP
	{
	public:
		SelectNodesOP(EditPanel* editPanel, MultiShapesImpl* shapesImpl, AbstractEditCMPT* callback = NULL);
		virtual ~SelectNodesOP();

		virtual bool onKeyDown(int keyCode);
		virtual bool onMouseLeftDown(int x, int y);
		virtual bool onMouseLeftUp(int x, int y);

		virtual bool onDraw() const;
		virtual bool clear();

		void fetchSelectedNode(std::vector<f2Vec2>& nodes) const;

		static int getThreshold();

	protected:
		void clearSelectedNodes();

	protected:
		struct ChainSelectedNodes
		{
		public:
			ChainShape* chain;
			std::vector<f2Vec2> selectedNodes;
		}; // ChainSelectedNodes

	private:
		class PosQueryVisitor : public IVisitor
		{
		public:
			PosQueryVisitor(const f2Vec2& pos, ChainSelectedNodes** result);
			virtual void visit(IObject* object, bool& bFetchNext);

		private:
			const f2Vec2& m_pos;
			f2AABB m_aabb;
			ChainSelectedNodes** m_result;

		}; // PosQueryVisitor

		class AABBQueryVisitor : public IVisitor
		{
		public:
			AABBQueryVisitor(const f2AABB& aabb, std::vector<ChainSelectedNodes*>& result);
			virtual void visit(IObject* object, bool& bFetchNext);

		private:
			const f2AABB& m_aabb;
			std::vector<ChainSelectedNodes*>& m_result;

		}; // AABBQueryVisitor

	protected:
		std::vector<ChainSelectedNodes*> m_nodeSelection;

	private:
		MultiShapesImpl* m_shapeImpl;

		f2Vec2 m_firstPos;

	}; // SelectNodesOP
}

#endif // _WX_GUI_SELECT_NODES_OP_H_