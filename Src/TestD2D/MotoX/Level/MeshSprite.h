#ifndef _MOTOX_MESH_SPRITE_H_
#define _MOTOX_MESH_SPRITE_H_

#include "IObstacleSprite.h"

namespace motox
{
	class MeshSprite : public IObstacleSprite
	{
	public:
		MeshSprite(float scale);
		virtual ~MeshSprite();

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
		float m_scale;

		d2d::Mesh* m_mesh;

		int m_meshID;

		d2d::Vector m_location;
		float m_angle;

	}; // MeshSprite
}

#endif // _MOTOX_MESH_SPRITE_H_