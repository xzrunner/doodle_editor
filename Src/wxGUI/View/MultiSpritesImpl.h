#ifndef _WX_GUI_MULTI_SPRITES_IMPL_H_
#define _WX_GUI_MULTI_SPRITES_IMPL_H_

#include "EditPanelDefs.h"

#include "Dataset/SelectionSet.h"

#include <wx/wx.h>

namespace wxgui
{
	class MultiSpritesImpl
	{
	public:
		MultiSpritesImpl(wxWindow* wnd);
		virtual ~MultiSpritesImpl();

		virtual void traverseSprites(IVisitor& visitor, 
			TraverseType type = e_allExisting, bool order = true) const = 0;
		virtual void removeSprite(ISprite* sprite) = 0;
		virtual void insertSprite(ISprite* sprite) = 0;
		virtual void clear() = 0;

		virtual ISprite* querySpriteByPos(const f2Vec2& pos) const;
		virtual void querySpritesByAABB(const f2AABB& aabb, std::vector<ISprite*>& result) const;		

		SpriteSelection* getSpriteSelection() { return m_spriteSelection; }
		void removeSpriteSelection();

	private:
		class PointQueryVisitor : public IVisitor
		{
		public:
			PointQueryVisitor(const f2Vec2& pos, ISprite** pResult);
			virtual void visit(IObject* object, bool& bFetchNext);

		private:
			const f2Vec2& m_pos;
			ISprite** m_pResult;

		}; // PointQueryVisitor

		class RectQueryVisitor : public IVisitor
		{
		public:
			RectQueryVisitor(const f2AABB& aabb, std::vector<ISprite*>& result);
			virtual void visit(IObject* object, bool& bFetchNext);

		private:
			const f2AABB& m_aabb;
			std::vector<ISprite*>& m_result;

		}; // RectQueryVisitor

		class RemoveSelectionVisitor : public IVisitor
		{
		public:
			RemoveSelectionVisitor(MultiSpritesImpl* spritesImpl);
			virtual void visit(IObject* object, bool& bFetchNext);

		private:
			MultiSpritesImpl* m_spritesImpl;

		}; // RemoveSelectionVisitor

	protected:
		wxWindow* m_wnd;

		SpriteSelection* m_spriteSelection;

	}; // MultiSpritesImpl
}

#endif // _WX_GUI_MULTI_SPRITES_IMPL_H_