#ifndef _FRUITS_ANIMATOR_COMPOSE_WHOLE_SKELETON_OP_H_
#define _FRUITS_ANIMATOR_COMPOSE_WHOLE_SKELETON_OP_H_

#include "Dataset/WholeSkeleton.h"

#include <wxGUI/wxGUI.h>

namespace FRUITS_ANIMATOR
{
	class SkeletonEditPanel;

	class ComposeWholeSkeletonOP : public wxgui::ArrangeSpriteOP
	{
	public:
		ComposeWholeSkeletonOP(SkeletonEditPanel* editPanel, 
			WholeSkeleton* skeleton, wxTextCtrl* layerTextCtrl);
		virtual ~ComposeWholeSkeletonOP();

		virtual bool onMouseLeftDown(int x, int y);
		virtual bool onMouseLeftUp(int x, int y);
		virtual bool onMouseRightUp(int x, int y);

		virtual bool onDraw() const;

		void absorbSprite(WholeSkeleton::Sprite* sprite);

		void setSelectedBoneLayer(int layer);

	protected:
		virtual void translateSprite(const f2Vec2& delta);
		virtual void rotateSprite(const f2Vec2& dst);

	private:
		void connect(WholeSkeleton::Sprite* parent, WholeSkeleton::Sprite* child,
			WholeSkeleton::Node* from, WholeSkeleton::Node* to);

		void updateLayerInfo();

		void translateToCenter();

	private:
		class NearestNodeVisitor : public IVisitor
		{
		public:
			NearestNodeVisitor(WholeSkeleton::Sprite* sprite, WholeSkeleton::Sprite** pResult, 
				WholeSkeleton::Node** pFromNode, WholeSkeleton::Node** pToNode);

			virtual void visit(IObject* object, bool& bFetchNext);

		private:
			WholeSkeleton::Sprite* m_sprite;

			WholeSkeleton::Sprite** m_pResult;
			WholeSkeleton::Node **m_pFromNode, **m_pToNode;

			float m_nearestDis;

		}; // NearestNodeVisitor

	private:
		WholeSkeleton* m_skeleton;

		WholeSkeleton::Sprite* m_selected;

		wxTextCtrl* m_layerTextCtrl;

	}; // ComposeWholeSkeletonOP
}

#endif // _FRUITS_ANIMATOR_COMPOSE_WHOLE_SKELETON_OP_H_