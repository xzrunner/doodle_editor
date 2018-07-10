#ifndef _WX_GUI_ARRANGE_SPRITE_OP_H_
#define _WX_GUI_ARRANGE_SPRITE_OP_H_

#include "Dataset/SelectionSet.h"

namespace wxgui
{
	class EditPanel;
	class MultiSpritesImpl;
	class PropertySettingPanel;
	class AbstractEditCMPT;

	template <typename TBase>
	class ArrangeSpriteOP : public TBase
	{
	public:
		ArrangeSpriteOP(EditPanel* editPanel, MultiSpritesImpl* spritesImpl, 
			PropertySettingPanel* propertyPanel, AbstractEditCMPT* callback = NULL,
			bool scaleOpen = true);
		virtual ~ArrangeSpriteOP();

		virtual bool onKeyDown(int keyCode);
		virtual bool onMouseLeftDown(int x, int y);
		virtual bool onMouseLeftUp(int x, int y);
		virtual bool onMouseRightDown(int x, int y);
		virtual bool onMouseRightUp(int x, int y);
		virtual bool onMouseDrag(int x, int y);

		virtual bool onDraw() const;
		virtual bool clear();

	protected:
		virtual void translateSprite(const f2Vec2& delta);
		virtual void rotateSprite(const f2Vec2& dst);
		virtual void scaleSprite(const f2Vec2& currPos);

	private:
		void setScalingFromSelected();

	private:
		class TranslateVisitor : public IVisitor
		{
		public:
			TranslateVisitor(const f2Vec2& delta);
			virtual void visit(IObject* object, bool& bFetchNext);

		private:
			const f2Vec2& m_delta;

		}; // TranslateVisitor

		class RotateVisitor : public IVisitor
		{
		public:
			RotateVisitor(const f2Vec2& start, const f2Vec2& end);
			virtual void visit(IObject* object, bool& bFetchNext);

		private:
			const f2Vec2 &m_start, &m_end;

		}; // RotateVisitor

	private:
		static const float SCALE_NODE_RADIUS;

	private:
		MultiSpritesImpl* m_spritesImpl;

		PropertySettingPanel* m_propertyPanel;

	protected:
		SpriteSelection* m_selection;
		f2Vec2 m_lastPos;

	private:
		bool m_scaleOpen;

		bool m_bRightPress;

		f2Vec2 m_firstPos;

		ISprite* m_scaling;
		f2Vec2 m_scaleSelected;

		bool m_bDirty;

	}; // ArrangeSpriteOP
}

#include "ArrangeSpriteOP.cpp"

#endif // _WX_GUI_ARRANGE_SPRITE_OP_H_