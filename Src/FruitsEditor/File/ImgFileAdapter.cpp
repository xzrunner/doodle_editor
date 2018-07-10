#include "ImgFileAdapter.h"
#include "../Dataset/Sprite.h"
#include "../Dataset/Texture.h"
#include "../Dataset/TextureRegion.h"

using namespace FEDITOR;

ImgFileAdapter::ImgFileAdapter()
{
	m_sprite = NULL;
}

void ImgFileAdapter::load(const std::string& filename)
{
	if (m_sprite)
	{
		m_sprite->clearTextureRegions();

		Texture* texture = TexturesMgr::Instance()->getItem(filename);
		m_sprite->setTexture(texture);

		const float hWidth = texture->getWidth() * 0.5f,
			hHeight = texture->getHeight() * 0.5f;

		TextureRegion* rightDown = new TextureRegion;
		rightDown->filename = texture->getFilename();
		rightDown->srcRegion[0].set(0, 0);
		rightDown->srcRegion[1].set(1, 0);
		rightDown->srcRegion[2].set(1, 1);
		rightDown->dstRegion[0].set(-hWidth, -hHeight);
		rightDown->dstRegion[1].set( hWidth, -hHeight);
		rightDown->dstRegion[2].set( hWidth,  hHeight);
		m_sprite->pushTextureRegion(rightDown);

		TextureRegion* leftUp = new TextureRegion;
		leftUp->filename = texture->getFilename();
		leftUp->srcRegion[0].set(0, 0);
		leftUp->srcRegion[1].set(1, 1);
		leftUp->srcRegion[2].set(0, 1);
		leftUp->dstRegion[0].set(-hWidth, -hHeight);
		leftUp->dstRegion[1].set( hWidth,  hHeight);
		leftUp->dstRegion[2].set(-hWidth,  hHeight);
		m_sprite->pushTextureRegion(leftUp);
	}
}