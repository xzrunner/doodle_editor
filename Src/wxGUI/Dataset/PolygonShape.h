#ifndef _WX_GUI_POLYGON_SHAPE_H_
#define _WX_GUI_POLYGON_SHAPE_H_

#include "ChainShape.h"

#include <wx/wx.h>

namespace wxgui
{
	class ImageSymbol;

	class PolygonShape : public ChainShape
	{
	public:
		enum FillingType
		{
			e_Color = 0,
			e_Texture,
			e_Null
		};

	public:
		PolygonShape(const PolygonShape& polygon);
		PolygonShape(const std::vector<f2Vec2>& vertices);
		virtual ~PolygonShape();
		
		//
		// IObject interface
		//
		virtual PolygonShape* clone();

		//
		// IShape interface
		//
		virtual void draw(const f2Colorf& color = f2Colorf(0, 0, 0)) const;

	public:
		void buildFillingTris();
		void buildFillingTris(const std::vector<f2Vec2>& segments);

	private:
		void getBoundingRegion(const std::vector<f2Vec2>& bounding, float& left, float& right, float& low, float& up);
		void getTextureBoundarySegments(float left, float right, float low, float up,
			std::vector<f2Vec2>& segments);
		void computeTextureCoords(float left, float low);

	public:
		int m_fillingType;

		f2Colorf m_fillingColor;
		ImageSymbol* m_fillingTexture;

		std::vector<f2Vec2> m_fillingVertices;
		std::vector<f2Vec2> m_fillingTexCoords;

	}; // PolygonShape
}

#endif // _WX_GUI_POLYGON_SHAPE_H_