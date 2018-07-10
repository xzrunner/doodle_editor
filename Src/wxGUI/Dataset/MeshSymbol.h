#ifndef _WX_GUI_MESH_SYMBOL_H_
#define _WX_GUI_MESH_SYMBOL_H_

#include "ISymbol.h"
#include "Image.h"

namespace wxgui
{
	class MeshSymbol : public ISymbol
	{
	public:
		MeshSymbol();
		virtual ~MeshSymbol();

		//
		// IObject interface
		//	
		virtual MeshSymbol* clone();

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

		const std::vector<f2Vec2>& getVertices() const;

	private:
		void loadResources();

	private:
		Image* m_image;

		std::vector<f2Vec2> m_vertices;
		std::vector<f2Vec2> m_texCoords;

	}; // MeshSymbol
}

#endif // _WX_GUI_MESH_SYMBOL_H_