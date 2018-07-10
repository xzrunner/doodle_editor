#ifndef _FEDITOR_BODY_FACTORY_H_
#define _FEDITOR_BODY_FACTORY_H_
#include <Fruits2D/Fruits2D.h>

class b2World;

namespace FEDITOR
{
	class Body;
	class Shape;
	class BodyData;

	class BodyFactory
	{
	public:
		static Body* createBody(const std::string& filename, float scale = 1.0f);

		static void setWorld(b2World* world);

	private:
		static b2World* m_world;

	}; // BodyFactory

	inline void BodyFactory::setWorld(b2World* world)
	{
		m_world = world;
	}
}

#endif // _FEDITOR_BODY_FACTORY_H_