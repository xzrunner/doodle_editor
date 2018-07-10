#ifndef _WX_GUI_EDIT_POLYLINES_OP_H_
#define _WX_GUI_EDIT_POLYLINES_OP_H_

#include "SelectShapesOP.h"

namespace wxgui
{
	class ChainShape;
	class EditPolylinesCMPT;

	class EditPolylinesOP : public SelectShapesOP
	{
	public:
		EditPolylinesOP(EditPanel* editPanel, MultiShapesImpl* shapesImpl,
			EditPolylinesCMPT* cmpt);

		virtual bool onMouseLeftDown(int x, int y);
		virtual bool onMouseLeftUp(int x, int y);
		virtual bool onMouseDrag(int x, int y);

		virtual bool onDraw() const;
		virtual bool clear();

		void simplify();
		void updateFromSimplified();

	private:
		void clearBuffer();

	private:
		class UpdateChainVisitor : public IVisitor
		{
		public:
			virtual void visit(IObject* object, bool& bFetchNext);
		}; // UpdateChainVisitor

		class UpdateBufferVisitor : public IVisitor
		{
		public:
			UpdateBufferVisitor(std::map<ChainShape*, ChainShape*>& simplifyBuffer);

			virtual void visit(IObject* object, bool& bFetchNext);

		private:
			std::map<ChainShape*, ChainShape*>& m_simplifyBuffer;

		}; // UpdateBufferVisitor

		class OffsetVisitor : public IVisitor
		{
		public:
			OffsetVisitor(const f2Vec2& offset);

			virtual void visit(IObject* object, bool& bFetchNext);

		private:
			const f2Vec2& m_offset;

		}; // OffsetVisitor

	private:
		EditPolylinesCMPT* m_cmpt;

		std::map<ChainShape*, ChainShape*> m_simplifyBuffer;

		f2Vec2 m_lastPos;

		bool m_bDirty;

	}; // EditPolylinesOP
}

#endif // _WX_GUI_EDIT_POLYLINES_OP_H_