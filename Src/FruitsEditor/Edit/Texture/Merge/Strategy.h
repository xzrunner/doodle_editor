#ifndef _FEDITOR_TEXTURE_MERGE_STRATEGY_H_
#define _FEDITOR_TEXTURE_MERGE_STRATEGY_H_
#include <Fruits2D/Fruits2D.h>

namespace FEDITOR
{
	class Sprite;

	namespace TEXTURE_MERGE
	{
		class Strategy
		{
		public:
			virtual ~Strategy() {}

			virtual void arrangeTextures(const std::vector<Sprite*>& sprites, int width, int height) = 0;

		protected:
			void sortByArea(std::vector<Sprite*>& sprites, bool isDescend = true) const;

		protected:
			class SpriteCmp
			{
			public:
				SpriteCmp(bool isDescend);

				bool operator() (const Sprite* s0, const Sprite* s1) const;

			private:
				bool m_isDescend;

			}; // SpriteCmp

		}; // Strategy

		class DirectlyStrategy : public Strategy
		{
		public:
			virtual void arrangeTextures(const std::vector<Sprite*>& sprites, int width, int height);

		private:

		}; // DirectlyStrategy

 		class BinaryTreeStrategy : public Strategy
 		{
 		public:
			BinaryTreeStrategy();
			virtual ~BinaryTreeStrategy();

			virtual void arrangeTextures(const std::vector<Sprite*>& sprites, int width, int height);
 
		private:
			void resetRoot(int width, int height);

		private:
			struct Node
			{
				Node* child[2];
				Sprite* texture;
				f2AABB rc;

				Node();
				~Node();

				Node* insert(Sprite* sprite, int flag);
			};

		private:
			Node* m_root;

 		}; // BinaryTreeStrategy
	}
}

#endif // _FEDITOR_TEXTURE_MERGE_STRATEGY_H_