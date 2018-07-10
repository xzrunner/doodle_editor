#ifndef _FEDITOR_CHAIN_SHAPE_ADDR_H_
#define _FEDITOR_CHAIN_SHAPE_ADDR_H_
#include <Fruits2D/Fruits2D.h>
#include "ChainShape.h"

namespace FEDITOR
{
	class Layer;
	class Sprite;
	class ChainShape;

	struct ChainShapeAddr
	{
		Layer* layer;
		Sprite* sprite;
		ChainShape* shape;
		int iPos;

		ChainShapeAddr();
		ChainShapeAddr(const ChainShapeAddr& addr);

		void setInvalid();

		bool isValid() const;

		f2Vec2 getPos() const;

	}; // ChainShapeAddr

	inline ChainShapeAddr::ChainShapeAddr()
	{
		setInvalid();
	}

	inline ChainShapeAddr::ChainShapeAddr(const ChainShapeAddr& addr)
	{
		layer = addr.layer;
		sprite = addr.sprite;
		shape = addr.shape;
		iPos = addr.iPos;
	}

	inline void ChainShapeAddr::setInvalid()
	{
		layer = NULL;
		sprite = NULL;
		shape = NULL;
		iPos = -1;
	}

	inline bool ChainShapeAddr::isValid() const
	{
		return layer != NULL && sprite != NULL && shape != NULL
			&& iPos != -1 && iPos < shape->m_vertices.size();
	}

	inline f2Vec2 ChainShapeAddr::getPos() const
	{
		if (isValid()) return shape->m_vertices[iPos];
		else return f2Vec2(0, 0);
	}
}

#endif // _FEDITOR_CHAIN_SHAPE_ADDR_H_