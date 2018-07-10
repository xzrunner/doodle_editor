#ifndef _WX_GUI_MULTI_SHAPES_IMPL_H_
#define _WX_GUI_MULTI_SHAPES_IMPL_H_

#include "EditPanelDefs.h"

#include "Dataset/SelectionSet.h"

#include <wx/wx.h>

namespace wxgui
{
	class MultiShapesImpl
	{
	public:
		MultiShapesImpl(wxWindow* wnd);
		virtual ~MultiShapesImpl();

		virtual void traverseShapes(IVisitor& visitor, 
			TraverseType type = e_allExisting) const = 0;
		virtual void removeShape(IShape* shape) = 0;
		virtual void insertShape(IShape* shape) = 0;
		virtual void clear() = 0;

		IShape* queryShapeByPos(const f2Vec2& pos) const;
		void queryShapesByAABB(const f2AABB& aabb, std::vector<IShape*>& result) const;		

		ShapeSelection* getShapeSelection() { return m_shapeSelection; }
		void removeShapeSelection();

	private:
		class PointQueryVisitor : public IVisitor
		{
		public:
			PointQueryVisitor(const f2Vec2& pos, IShape** pResult);
			virtual void visit(IObject* object, bool& bFetchNext);

		private:
			const f2Vec2& m_pos;
			IShape** m_pResult;

		}; // PointQueryVisitor

		class RectQueryVisitor : public IVisitor
		{
		public:
			RectQueryVisitor(const f2AABB& aabb, std::vector<IShape*>& result);
			virtual void visit(IObject* object, bool& bFetchNext);

		private:
			const f2AABB& m_aabb;
			std::vector<IShape*>& m_result;

		}; // RectQueryVisitor

		class RemoveSelectionVisitor : public IVisitor
		{
		public:
			RemoveSelectionVisitor(MultiShapesImpl* shapesImpl);
			virtual void visit(IObject* object, bool& bFetchNext);

		private:
			MultiShapesImpl* m_shapesImpl;

		}; // RemoveSelectionVisitor

	protected:
		wxWindow* m_wnd;

		ShapeSelection* m_shapeSelection;

	}; // MultiShapesImpl
}

#endif // _WX_GUI_MULTI_SHAPES_IMPL_H_