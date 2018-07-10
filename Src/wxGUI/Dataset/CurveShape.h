#ifndef _WX_GUI_CURVE_SHAPE_H_
#define _WX_GUI_CURVE_SHAPE_H_

#include "ChainShape.h"

namespace wxgui
{
	class CurveShape : public ChainShape
	{
	public:
		CurveShape(const CurveShape& curve);
		CurveShape(const std::vector<f2Vec2>& vertices);
		virtual ~CurveShape();

		//
		// IObject interface
		//
		virtual CurveShape* clone();

		//
		// IShape interface
		//
		virtual void draw(const f2Colorf& color = f2Colorf(0, 0, 0)) const;

		//
		// ChainShape interface
		//
		virtual void insertVertices(size_t index, const f2Vec2& pos);
		virtual void removeVertices(const f2Vec2& pos);
		virtual void changeVertices(const f2Vec2& from, const f2Vec2& to);
		virtual void refresh();

		const std::vector<f2Vec2>& getMidPoints() const { return m_midPoints; }
		void setMidPoints();

	private:
		static const float SAMPLING_WIDTH;

	private:
		std::vector<f2Vec2> m_midPoints;

	}; // CurveShape
}

#endif // _WX_GUI_CURVE_SHAPE_H_