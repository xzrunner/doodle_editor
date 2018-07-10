#ifndef _F2D_SPRITE_H_
#define _F2D_SPRITE_H_

#include "Object.h"

#include "Tools/Tools.h"
#include "Tools/f2Types.h"
#include "Tools/UserDataImpl.h"

namespace F2D
{
	class AbstractBV;

	class f2Sprite : public IObject, public UserDataImpl, public Object
	{
	public:
		f2Sprite();
		f2Sprite(const f2Sprite& sprite);
		virtual ~f2Sprite();

		//
		// IObject interface
		//
		virtual f2Sprite* clone() { return NULL; }

		//
		// UserDataImpl interface
		//	
		virtual void clearUserData(bool deletePtr);

		virtual void setTransform(const f2Vec2& position, float angle);
		virtual void setScale(float scale) { m_scale = scale; }

		bool isContain(const f2Vec2& pos) const;
		bool isIntersect(const f2AABB& aabb) const;

		void translate(const f2Vec2& offset);
		void rotate(float delta);

		const f2Vec2& getPosition() const;
		float getAngle() const;
		float getScale() const { return m_scale; }

		void setMirror(bool xMirror, bool yMirror) { m_xMirror = xMirror; m_yMirror = yMirror; }
		void getMirror(bool& xMirror, bool& yMirror) const { xMirror = m_xMirror; yMirror = m_yMirror; }

		AbstractBV* getBounding() const;

	protected:
		f2Vec2 m_pos;
		float m_angle;
		float m_scale;

		bool m_xMirror, m_yMirror;

		AbstractBV* m_bounding;

	}; // f2Sprite
}

#endif // _F2D_SPRITE_H_