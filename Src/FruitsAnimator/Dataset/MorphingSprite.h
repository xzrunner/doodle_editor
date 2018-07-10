#ifndef _FRUITS_ANIMATOR_MORPHING_SPRITE_H_
#define _FRUITS_ANIMATOR_MORPHING_SPRITE_H_

#include "Sprite.h"

namespace FRUITS_ANIMATOR
{
	class Symbol;
	class Mesh;
	class PartSkeleton;
	class LibraryPanel;

	class MorphingSprite : public Sprite
	{
	public:
		MorphingSprite();
		MorphingSprite(Symbol* symbol, const f2Vec2& pos, bool isCopyMesh);
		MorphingSprite(const MorphingSprite& sprite);
		virtual ~MorphingSprite();

		//
		// IObject interface
		//
		virtual MorphingSprite* clone();

		virtual void loadFromTextFile(std::ifstream& fin, const LibraryPanel& library);
		virtual void storeToTextFile(std::ofstream& fout, const LibraryPanel& library) const;

		virtual Symbol* getSymbol() { return m_symbol; }
		virtual Mesh* getMesh() { return m_mesh; }
		virtual PartSkeleton* getPartSkeleton() { return m_skeleton; }
		virtual WholeSkeleton* getWholeSkeleton() { return NULL; }

		virtual void reloadTexture();

	private:
		void clear();

		void initBounding(Symbol* symbol);

	private:
		Symbol* m_symbol;

		Mesh* m_mesh;
		PartSkeleton* m_skeleton;

	}; // MorphingSprite
}

#endif // _FRUITS_ANIMATOR_MORPHING_SPRITE_H_