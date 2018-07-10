#ifndef _FEDITOR_TEXTURE_REGION_H_
#define _FEDITOR_TEXTURE_REGION_H_
#include <Fruits2D/Fruits2D.h>

namespace FEDITOR
{
	class TextureRegion : public IObject, public ISerializable
	{
	public:
		TextureRegion();
		TextureRegion(const TextureRegion& region);

		//
		// IObject interface
		//
		virtual TextureRegion* clone();

		//
		// ISerializable interface
		//
		virtual void loadFromTextFile(std::ifstream& fin);
		virtual void storeToTextFile(std::ofstream& fout) const;

		bool isContain(const f2Vec2& pos) const;
		void getAABB(f2AABB& aabb, const f2Vec2& position, float angle) const;

	public:
		std::string filename;
		f2Vec2 srcRegion[3], dstRegion[3];

	}; // TextureRegion
}

#endif // _FEDITOR_TEXTURE_REGION_H_