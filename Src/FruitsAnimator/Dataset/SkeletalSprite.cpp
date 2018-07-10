#include "SkeletalSprite.h"
#include "WholeSkeleton.h"
#include "SpriteFactory.h"
#include "Symbol.h"
#include "View/LibraryPanel.h"

using namespace FRUITS_ANIMATOR;

SkeletalSprite::SkeletalSprite()
{
	m_src = m_skeleton = NULL;
}

SkeletalSprite::SkeletalSprite(WholeSkeleton* skeleton)
{
	m_src = skeleton;
	m_skeleton = skeleton->clone();
	initBounding();
}

SkeletalSprite::SkeletalSprite(const SkeletalSprite& sprite)
	: Sprite(sprite)
{
	m_src = sprite.m_src;
	m_skeleton = sprite.m_skeleton->clone();
}

SkeletalSprite::~SkeletalSprite()
{
	delete m_skeleton;
}

SkeletalSprite* SkeletalSprite::clone()
{
	return new SkeletalSprite(*this);
}

void SkeletalSprite::loadFromTextFile(std::ifstream& fin, const LibraryPanel& library)
{
	fin >> m_pos >> m_angle;

	int index;
	fin >> index;
	assert(index != -1);
	m_src = library.getSkeleton(index);
	m_skeleton = library.getSkeleton(index)->clone();

	int size;
	fin >> size;
	std::vector<WholeSkeleton::Sprite*> sprites;
	m_skeleton->traverse(WholeSkeleton::FetchAllBonesVisitor(sprites));
	assert(size == sprites.size());
	for (size_t i = 0, n = sprites.size(); i < n; ++i)
		sprites[i]->loadFromTextFile(fin);
	
	initBounding();
}

void SkeletalSprite::storeToTextFile(std::ofstream& fout, const LibraryPanel& library) const
{
	fout << SpriteFactory::e_skeletal << " " 
		<< m_pos << " " << m_angle << " "
		<< library.getIndex(m_src) << " ";

	std::vector<WholeSkeleton::Sprite*> sprites;
	m_skeleton->traverse(WholeSkeleton::FetchAllBonesVisitor(sprites));
	fout << sprites.size() << '\n';
	for (size_t i = 0, n = sprites.size(); i < n; ++i)
		sprites[i]->storeToTextFile(fout);
}

void SkeletalSprite::reloadTexture()
{
	m_skeleton->traverse(ReloadTextureVisitor());
}

void SkeletalSprite::initBounding()
{
	m_bounding = BVFactory::createBV(e_obb);
	m_skeleton->getBounding(*m_bounding);
}

///////////////////////////////////////////////////////////////////////////
// class SkeletalSprite::ReloadTextureVisitor
//////////////////////////////////////////////////////////////////////////

void SkeletalSprite::ReloadTextureVisitor::visit(IObject* object, bool& bFetchNext)
{
	WholeSkeleton::Sprite* bone = static_cast<WholeSkeleton::Sprite*>(object);
	bone->getSymbol()->reloadTexture();
	bFetchNext = true;
}