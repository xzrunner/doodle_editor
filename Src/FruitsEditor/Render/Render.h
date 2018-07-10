#ifndef _FEDITOR_RENDER_H_
#define _FEDITOR_RENDER_H_
#include <Fruits2D/Fruits2D.h>

namespace F2D
{
	class AbstractBV;
}

namespace FEDITOR
{
	class Sprite;
	class Layer;
	class LayerRenderStyle;
	class TextureRegion;
	class Shape;
	class SelectionSet;
	class AbstractBV;

	class Render
	{
	public:
		static void drawLayers(const std::vector<Layer*>& layers);
		static void drawSelection(const SelectionSet& selection);

	private:
		static void drawLayer(const Layer* layer);

		static void drawSprite(const Sprite* sprite, const LayerRenderStyle& style);
		static void drawSpriteShape(const Sprite* sprite, const LayerRenderStyle& style, int typeFilter = -1);
		static void drawSpriteTexture(const Sprite* sprite);

		static void drawShapes(const std::vector<Shape*>& shapes, const LayerRenderStyle& style, int typeFilter = -1);
	public:
		static void drawTextures(const std::vector<TextureRegion*>& textures);
	private:
		static void drawAABB(F2D::AbstractBV* bounding);

	private:
		static void drawSelection(const Sprite* sprite);

		static void drawTexturesSelected(const std::vector<TextureRegion*>& textures);
		static void drawShapesSelected(const std::vector<Shape*>& shapes);

	private:
		static void drawPoints(const std::vector<f2Vec2>& points, float size, f2Colorf color);
		static void drawPolyline(const std::vector<f2Vec2>& line, float width, f2Colorf color, bool isLoop = false);
		static void drawTriangle(const f2Vec2 pos[3], f2Colorf color);
		static void drawAABB(const f2AABB& aabb);

	}; // Render
}

#endif // _FEDITOR_RENDER_H_