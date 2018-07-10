#ifndef _MOTOX_COMMON_SPRITE_H_
#define _MOTOX_COMMON_SPRITE_H_

#include "IObstacleSprite.h"

namespace motox
{
	class CommonSprite : public IObstacleSprite
	{
	public:
		CommonSprite();
		virtual ~CommonSprite();

		virtual void setTransform(const d2d::Vector& location, float angle);

		virtual void update();

		virtual void addToBatch(d2d::MeshBatch* batch) const;

		virtual const d2d::Vector& getPosition() const { 
			return m_graphics->getLocation(); 
		}
		virtual float getAngle() const { 
			return m_graphics->getAngle(); 
		}

	public:
		d2d::GraphicsSprite* m_graphics;

		int m_texID;

	}; // CommonSprite
}

#endif // _MOTOX_COMMON_SPRITE_H_