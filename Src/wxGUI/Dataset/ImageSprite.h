#ifndef _WX_GUI_IMAGE_SPRITE_H_
#define _WX_GUI_IMAGE_SPRITE_H_

#include "ISprite.h"

#include "ImageSymbol.h"

namespace wxgui
{
	class ImageSymbol;

	class ImageSprite : public ISprite
	{
	public:
		ImageSprite();
		ImageSprite(const ImageSprite& sprite);
		ImageSprite(ImageSymbol* symbol);

		//
		// IObject interface
		//
		virtual ImageSprite* clone();

		//
		// ISprite interface
		//
		virtual const ImageSymbol& getSymbol() const;
		virtual void setSymbol(ISymbol* symbol);
		virtual void loadBodyFromFile();

		// todo: should auto resize through its symbol and shapes
		void buildBounding(float* texCoords);

	protected:
		virtual void buildBounding();

	protected:
		ImageSymbol* m_symbol;

	}; // ImageSprite
}

#endif // _WX_GUI_IMAGE_SPRITE_H_