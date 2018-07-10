#ifndef _FRUITS_ANIMATOR_SKELETAL_SPRITE_H_
#define _FRUITS_ANIMATOR_SKELETAL_SPRITE_H_

#include "Sprite.h"

namespace FRUITS_ANIMATOR
{
	class WholeSkeleton;
	class LibraryPanel;

	class SkeletalSprite : public Sprite
	{
	public:
		SkeletalSprite();
		SkeletalSprite(WholeSkeleton* skeleton);
		SkeletalSprite(const SkeletalSprite& sprite);
		virtual ~SkeletalSprite();

		//
		// IObject interface
		//
		virtual SkeletalSprite* clone();

		void loadFromTextFile(std::ifstream& fin, const LibraryPanel& library);
		void storeToTextFile(std::ofstream& fout, const LibraryPanel& library) const;

		virtual Symbol* getSymbol() { return NULL; }
		virtual Mesh* getMesh() { return NULL; }
		virtual PartSkeleton* getPartSkeleton() { return NULL; }
		virtual WholeSkeleton* getWholeSkeleton() { return m_skeleton; }

		virtual void reloadTexture();

	private:
		void initBounding();

	private:
		class ReloadTextureVisitor : public IVisitor
		{
		public:
			virtual void visit(IObject* object, bool& bFetchNext);
		}; // ReloadTextureVisitor

	private:
		WholeSkeleton* m_src;
		WholeSkeleton* m_skeleton;

	}; // SkeletalSprite
}

#endif // _FRUITS_ANIMATOR_SKELETAL_SPRITE_H_