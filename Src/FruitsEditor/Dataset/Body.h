#ifndef _FEDITOR_BODY_H_
#define _FEDITOR_BODY_H_
#include <Fruits2D/Fruits2D.h>

class b2World;
class b2Body;
struct b2Filter;

namespace FEDITOR
{
	class Body : public IObject
	{
	public:
		virtual ~Body();

		//
		// IObject interface
		//
		virtual Body* clone();

		virtual void getAABB(f2AABB& aabb, const f2Vec2& position, float angle) const = 0;

		b2Body* getBody() const;
		void setBody(b2Body* body);

		const std::string& getFilename() const;

		bool isAlive() const;
		void setAlive(bool isAlive);

		void setDensity(float density);
		void setFriction(float friction);
		void setCollisionFilter(const b2Filter& filter);

		void setTransform(const f2Vec2& pos, float angle);

	protected:
		Body(b2World* world, float scale = 1.0f);

	protected:
		std::string m_filename;

		bool m_alive;

		b2World* m_world;
		b2Body* m_body;

	private:
		float m_scale;

	}; // Body

	inline b2Body* Body::getBody() const
	{
		return m_body;
	}

	inline void Body::setBody(b2Body* body)
	{
		m_body = body;
	}

	inline const std::string& Body::getFilename() const
	{
		return m_filename;
	}

	inline bool Body::isAlive() const
	{
		return m_alive;
	}

	inline void Body::setAlive(bool isAlive)
	{
		m_alive = isAlive;
	}
}

#endif // _FEDITOR_BODY_H_