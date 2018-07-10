#include "TextureRegion.h"
#include "Texture.h"

using namespace FEDITOR;

TextureRegion::TextureRegion()
{
}

TextureRegion::TextureRegion(const TextureRegion& region)
{
	filename = region.filename;
	memcpy(&srcRegion[0], &region.srcRegion[0], sizeof(f2Vec2) * 3);
	memcpy(&dstRegion[0], &region.dstRegion[0], sizeof(f2Vec2) * 3);
}

TextureRegion* TextureRegion::clone()
{
	return new TextureRegion(*this);
}

void TextureRegion::loadFromTextFile(std::ifstream& fin)
{
	fin >> filename;
	TexturesMgr::Instance()->getItem(filename);
	for (size_t i = 0; i < 3; ++i)
		fin >> srcRegion[i];
	for (size_t i = 0; i < 3; ++i)
		fin >> dstRegion[i];
}

void TextureRegion::storeToTextFile(std::ofstream& fout) const
{
	fout << filename << '\n';
	for (size_t i = 0; i < 3; ++i)
		fout << srcRegion[i] << " ";
	fout << '\n';
	for (size_t i = 0; i < 3; ++i)
		fout << dstRegion[i] << " ";
	fout << '\n';
}

bool TextureRegion::isContain(const f2Vec2& pos) const
{
	return f2Math::isPointInTriangle(pos, dstRegion[0], dstRegion[1], dstRegion[2]);
}

void TextureRegion::getAABB(f2AABB& aabb, const f2Vec2& position, float angle) const
{
	aabb.makeInfinite();
	for (size_t i = 0; i < 3; ++i)
	{
		const f2Vec2& src = dstRegion[i];
		f2Vec2 transform = f2Math::rotateVector(src, angle) + position;
		aabb.combine(transform);
	}
}