#ifndef _WX_GUI_SHAPE_SYMBOL_H_
#define _WX_GUI_SHAPE_SYMBOL_H_

#include "ISymbol.h"

namespace wxgui
{
	class IShape;

	class ShapeSymbol : public ISymbol
	{
	public:
		ShapeSymbol();
		ShapeSymbol(const ShapeSymbol& symbol);
		virtual ~ShapeSymbol();

		//
		// IObject interface
		//	
		virtual ShapeSymbol* clone();

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

		const std::vector<IShape*>& getAllShapes() const { 
			return m_shapes; 
		}

	private:
		void loadResources();

		void clear();

	private:
		std::vector<IShape*> m_shapes;

	}; // ShapeSymbol
}

#endif // _WX_GUI_SHAPE_SYMBOL_H_