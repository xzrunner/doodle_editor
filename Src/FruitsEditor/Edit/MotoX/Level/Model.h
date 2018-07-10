#ifndef _FEDITOR_MOTOX_LEVEL_MODEL_H_
#define _FEDITOR_MOTOX_LEVEL_MODEL_H_
#include "../../AbstractModel.h"
#include "TrackChains.h"

class b2World;

namespace FEDITOR
{
	class Sprite;
	class Layer;
	class AbstractBlackboard;

	namespace MOTOX
	{
		class Actor;

		namespace LEVEL
		{
			class Blackboard;

			class Model : public AbstractModel
			{
			public:
				Model(const AbstractBlackboard* blackboard, b2World* world, b2World* worldReverse);
				virtual ~Model();

				virtual void handleEvent(const Event& event);

				TrackChains& getTrackChains();

				Layer* getTrackChainsLayer() const;

				f2Vec2 getActorPos() const;

				void addToBodySpriteMap(Sprite* sprite);
				void eraseFromBodySpriteMap(b2Body* body);
				Sprite* querySpriteByBody(b2Body* body) const;

			private:
				static const int MAX_SCREEN_WIDTH_TIMES = 1000;
				static const int DIVIDE_WIDTH_TIMES = 50;

			private:
				void initLayers();
				void initBgSprites();
				void initBgGridsSprite();
				void initActorParams();

				void storeAllSpritesToFile() const;
				void loadAllSpritesFromFile(const std::string& filename);

			private:
				const Blackboard* m_blackboard;

				b2World *m_world, *m_worldReverse;

				Layer* m_bgLayer;
				Sprite *m_bgTextureSprite, *m_bgShapeSprite;

				TrackChains m_trackChains;

				Layer* m_actorLayer;
				Actor* m_actor;

				std::map<b2Body*, Sprite*> m_mapBodyToSprite;

			}; // Model

			inline TrackChains& Model::getTrackChains()
			{
				return m_trackChains;
			}

			inline Layer* Model::getTrackChainsLayer() const
			{
				return m_trackChains.getLayer();
			}
		}
	}
}

#endif // _FEDITOR_MOTOX_LEVEL_MODEL_H_