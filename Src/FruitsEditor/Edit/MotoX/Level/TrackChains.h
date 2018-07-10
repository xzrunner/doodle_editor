#ifndef _FEDITOR_MOTOX_LEVEL_TRACK_CHAINS_H_
#define _FEDITOR_MOTOX_LEVEL_TRACK_CHAINS_H_
#include <Fruits2D/Fruits2D.h>

class b2Body;
class b2World;
class b2ChainShape;

namespace FEDITOR
{
	class Shape;
	class Sprite;
	class Layer;
	class LayersMgr;

	namespace MOTOX
	{
		namespace LEVEL
		{
			class TrackChains
			{
			public:
				TrackChains(b2World* world, b2World* worldReverse);

				void initialize(LayersMgr* layersMgr);

				void loadFromFile(const std::string& filename, b2World* world, b2World* worldReverse);
				void storeToFile(const std::string& filename) const;

				void setCtlposDrawable(bool draw);

				Sprite* getShapeSprite() const;

				void addFixtureFromLastChain();

				void createPhysFromAllChains();

				Layer* getLayer() const;

				b2Body* getBody() const;
				b2Body* getReverseBody() const;

				void setFriction(float friction);

			private:
				void createShapeFromChain(Shape* chain, b2ChainShape& b2Shape);

				void setBodyType();

			private:
				b2World *m_world, *m_worldReverse;

				Layer* m_layer;

				Sprite* m_phys;
				Sprite* m_physReverse;
				Sprite* m_shapes;

			}; // TrackChainSprites

			inline Layer* TrackChains::getLayer() const
			{
				return m_layer;
			}
		}
	}
}

#endif // _FEDITOR_MOTOX_LEVEL_TRACK_CHAINS_H_