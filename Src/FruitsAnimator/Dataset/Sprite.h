#ifndef _FRUITS_ANIMATOR_SPRITE_H_
#define _FRUITS_ANIMATOR_SPRITE_H_

#include <Fruits2D/Fruits2D.h>

namespace FRUITS_ANIMATOR
{
	class LibraryPanel;
	class Symbol;
	class Mesh;
	class PartSkeleton;
	class WholeSkeleton;

	class Sprite : public f2Sprite
	{
	public:

		virtual ~Sprite() {}

		//
		// IObject interface
		//
		virtual Sprite* clone() { return NULL; }

		virtual void loadFromTextFile(std::ifstream& fin, const LibraryPanel& library) = 0;
		virtual void storeToTextFile(std::ofstream& fout, const LibraryPanel& library) const = 0;

 		virtual Symbol* getSymbol() = 0;
 		virtual Mesh* getMesh() = 0;
 		virtual PartSkeleton* getPartSkeleton() = 0;
		virtual WholeSkeleton* getWholeSkeleton() = 0;

		virtual void reloadTexture() = 0;

	}; // Sprite
}

#endif // _FRUITS_ANIMATOR_SPRITE_H_