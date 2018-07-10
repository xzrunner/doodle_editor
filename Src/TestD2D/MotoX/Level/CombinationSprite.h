#ifndef _MOTOX_COMBINATION_SPRITE_H_
#define _MOTOX_COMBINATION_SPRITE_H_

#include "IObstacleSprite.h"

namespace motox
{
	class CombinationSprite : public IObstacleSprite
	{
	public:
		CombinationSprite();
		virtual ~CombinationSprite();

		virtual void setTransform(const d2d::Vector& location, float angle);

		virtual void update();

		virtual void addToBatch(d2d::MeshBatch* batch) const;

		virtual const d2d::Vector& getPosition() const { 
			return m_location; 
		}
		virtual float getAngle() const { 
			return m_angle; 
		}

	public:
		struct Part : public d2d::Object
		{
			IObstacleSprite* sprite;
			d2d::Vector offset;
			float delta;
			float scale;

			Part() : sprite(NULL), delta(0), scale(0) {}
			~Part() { 
				sprite->release(); 
			}
		};

	public:
		std::vector<Part*> m_children;

		d2d::Vector m_location;
		float m_angle;

	}; // CombinationSprite
}

#endif // _MOTOX_COMBINATION_SPRITE_H_