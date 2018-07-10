#ifndef _FEDITOR_EDIT_POLYLINE_OPERATION_H_
#define _FEDITOR_EDIT_POLYLINE_OPERATION_H_
#include "AbstractOp.h"
#include "../../Dataset/ChainShapeAddr.h"

namespace FEDITOR
{
	class Layer;
	class NodeCaptureCmpt;
	class Shape;
	class Sprite;

	class EditPolylineOP : public AbstractOp
	{
	public:
		EditPolylineOP(AbstractControl* task, Layer* editable, NodeCaptureCmpt* capture, AbstractEditOpCB* callback = NULL);
		virtual ~EditPolylineOP();

		virtual void onKeyboard(unsigned char key);
		virtual void onMouseLeftDown(int x, int y);
		virtual void onMouseLeftUp(int x, int y);
		virtual bool onMouseRightDown(int x, int y);
		virtual bool onMouseRightUp(int x, int y);
		virtual void onMouseMove(int x, int y);
		virtual void onMouseDrag(int x, int y);

	private:
		void prepareSelectDraw();

		bool selectPos(const f2Vec2& pos);
		bool selectPos(const f2Vec2& pos, Sprite* sprite);
		bool selectPos(const f2Vec2& pos, Shape* shape);

		void selectPosByAABB(const f2AABB& aabb);
		
		bool insertPos(const f2Vec2& pos);
		bool insertPos(const f2Vec2& pos, Sprite* sprite);
		bool insertPos(const f2Vec2& pos, Shape* shape);

		float getCaptureTolerance() const;

	private:
		static const int CAPTURE_TOL = 5;

	private:
		Layer* m_editable;

		NodeCaptureCmpt* m_capture;

		ChainShapeAddr m_selected;

		f2Vec2 m_lastPos;
		// todo
		f2Vec2 m_firstPos;

		Layer* m_tmpLayer;
		Sprite* m_tmpSprite;
		ChainShape* m_tmpShape;
		//

		std::vector<ChainShapeAddr> m_batchSelected;

	}; // EditPolylineOP
}

#endif // _FEDITOR_EDIT_POLYLINE_OPERATION_H_