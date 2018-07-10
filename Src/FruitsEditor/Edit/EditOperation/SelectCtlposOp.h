#ifndef _FEDITOR_SELECT_CTLPOS_OPERATION_H_
#define _FEDITOR_SELECT_CTLPOS_OPERATION_H_
#include "AbstractOp.h"

namespace FEDITOR
{
	class ChainShape;
	class Sprite;
	class Layer;
	class SelectionSet;

	class SelectCtlposOp : public AbstractOp
	{
	public:
		SelectCtlposOp(AbstractControl* task, Layer* editable);
		virtual ~SelectCtlposOp();

		virtual void onMouseLeftDown(int x, int y);
		virtual void onMouseLeftUp(int x, int y);
		virtual bool onMouseRightDown(int x, int y);
		virtual void onMouseDrag(int x, int y);

		SelectionSet& getSelection();

		const std::vector<f2Vec2>& getSelectedCtlpos() const;

	private:
		void prepareSelectDraw();

		void selectCtlpos(const f2AABB& aabb);

	private:
		Layer* m_dataLayer;
		SelectionSet& m_selection;

		// todo
		f2Vec2 m_firstPos;

		Layer* m_tmpLayer;
		Sprite* m_tmpSprite;
		ChainShape* m_tmpShape;
		//

		std::vector<f2Vec2> m_selectedCtlpos;

	}; // SelectCtlposOp

	inline SelectionSet& SelectCtlposOp::getSelection()
	{
		return m_selection;
	}
}

#endif // _FEDITOR_SELECT_CTLPOS_OPERATION_H_