#ifndef _WX_GUI_MESH_SPRITE_H_
#define _WX_GUI_MESH_SPRITE_H_

#include "ISprite.h"

#include "MeshSymbol.h"

namespace wxgui
{
	class MeshSprite;

	class MeshSprite : public ISprite
	{
	public:
		MeshSprite();
		MeshSprite(const MeshSprite& sprite);
		MeshSprite(MeshSymbol* symbol);
		virtual ~MeshSprite();

		//
		// IObject interface
		//
		virtual MeshSprite* clone();

		//
		// Sprite interface
		//
		virtual const MeshSymbol& getSymbol() const;
		virtual void setSymbol(ISymbol* symbol);
		virtual void loadBodyFromFile();

	protected:
		virtual void buildBounding();

	private:
		MeshSymbol* m_symbol;

	}; // MeshSprite
}

#endif // _WX_GUI_MESH_SPRITE_H_