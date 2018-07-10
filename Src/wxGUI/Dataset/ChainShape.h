#ifndef _WX_GUI_CHAIN_SHAPE_H_
#define _WX_GUI_CHAIN_SHAPE_H_

#include "IShape.h"

namespace wxgui
{
	class ChainShape : public IShape
	{
	public:
		ChainShape();
		ChainShape(const ChainShape& chain);
		ChainShape(const std::vector<f2Vec2>& vertices, bool isLoop);

		//
		// IObject interface
		//
		virtual ChainShape* clone();

		//
		// ISerializable interface
		//
		virtual void loadFromTextFile(std::ifstream& fin);
		virtual void storeToTextFile(std::ofstream& fout) const;

		//
		// f2Shape interface
		//
		virtual bool isContain(const f2Vec2& pos);
		virtual bool isIntersect(const f2AABB& aabb);

		//
		// IShape interface
		//
		virtual const f2AABB& getAABB() const { return m_bounding; }
		virtual void draw(const f2Colorf& color = f2Colorf(0, 0, 0)) const;

		virtual void insertVertices(size_t index, const f2Vec2& pos);
		// todo: too slow! 
		// cache index or pointer? how to avoid iterator's invalid
		// maybe use list instead of array, but others' effective? 
 		virtual void removeVertices(const f2Vec2& pos);
 		virtual void changeVertices(const f2Vec2& from, const f2Vec2& to);
		virtual void setVertices(const std::vector<f2Vec2>& vertices);
		virtual void refresh() {}

		void setClosed(bool isClose) { m_isLoop = isClose; }
		bool isClosed() const { return m_isLoop; }

		const std::vector<f2Vec2>& getVertices() const { return m_vertices; }

	private:
		void initBounding();

	protected:
		std::vector<f2Vec2> m_vertices;
		bool m_isLoop;

		f2AABB m_bounding;

	}; // ChainShape
}

#endif // _WX_GUI_CHAIN_SHAPE_H_