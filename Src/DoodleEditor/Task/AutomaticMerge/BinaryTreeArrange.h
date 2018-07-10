#ifndef _DEDITOR_AUTOMATIC_MERGE_BINARY_TREE_ARRANGE_H_
#define _DEDITOR_AUTOMATIC_MERGE_BINARY_TREE_ARRANGE_H_

#include "BaseStrategy.h"

namespace deditor
{
	namespace automatic_merge
	{
		class BinaryTreeArrange : public BaseStrategy
		{
		public:
			BinaryTreeArrange();
			virtual ~BinaryTreeArrange();

			virtual void arrange(const std::vector<wxgui::ImageSprite*>& sprites, 
				int width, int height);

		private:
			void resetRoot(int width, int height);

		private:
			struct Node
			{
				Node* child[2];
				wxgui::ISprite* texture;
				f2AABB rc;

				Node();
				~Node();

				Node* insert(wxgui::ImageSprite* sprite, int flag);
			};

			static const int REINSERT_MAX = 128;
			static const int SPACING = 128;

		private:
			Node* m_root;

		}; // BinaryTreeArrange
	}
}

#endif // _DEDITOR_AUTOMATIC_MERGE_BINARY_TREE_ARRANGE_H_