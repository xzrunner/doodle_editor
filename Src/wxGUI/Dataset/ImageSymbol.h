#ifndef _WX_GUI_IMAGE_SYMBOL_H_
#define _WX_GUI_IMAGE_SYMBOL_H_

#include "ISymbol.h"
#include "Image.h"

namespace wxgui
{
	class Image;

	class ImageSymbol : public ISymbol
	{
	public:
		ImageSymbol();
		virtual ~ImageSymbol();

		//
		// IObject interface
		//	
		virtual ImageSymbol* clone();

		//
		// ISerializable interface
		//
		virtual void loadFromTextFile(std::ifstream& fin);
		virtual void storeToTextFile(std::ofstream& fout) const;

		//
		// ISymbol interface
		//
		virtual void reloadTexture() const;
		virtual void draw() const;
		virtual float getWidth() const;
		virtual float getHeight() const;

		unsigned int getTextureID() const;

	protected:
		virtual void loadResources();

	protected:
		Image* m_image;

	}; // ImageSymbol
}

#endif // _WX_GUI_IMAGE_SYMBOL_H_