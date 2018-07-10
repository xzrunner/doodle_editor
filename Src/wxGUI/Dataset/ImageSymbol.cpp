#include "ImageSymbol.h"
#include "Bitmap.h"

using namespace wxgui;

ImageSymbol::ImageSymbol()
	: m_image(NULL)
{
}

ImageSymbol::~ImageSymbol()
{

}

ImageSymbol* ImageSymbol::clone()
{
	return NULL;
}

void ImageSymbol::loadFromTextFile(std::ifstream& fin)
{
}

void ImageSymbol::storeToTextFile(std::ofstream& fout) const
{
}

void ImageSymbol::reloadTexture() const
{
	m_image->reload();
}

void ImageSymbol::draw() const
{
	m_image->draw();
}

float ImageSymbol::getWidth() const
{
	return m_image->width();
}

float ImageSymbol::getHeight() const
{
	return m_image->height();
}

unsigned int ImageSymbol::getTextureID() const
{
	return m_image->textureID();
}

void ImageSymbol::loadResources()
{
	const Bitmap* init = BitmapMgr::Instance()->getItem(m_filepath);
	if (m_bitmap != init) delete m_bitmap;
	m_bitmap = const_cast<Bitmap*>(init);

	m_image = ImageMgr::Instance()->getItem(m_filepath);
}