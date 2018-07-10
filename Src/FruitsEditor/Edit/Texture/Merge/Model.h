#ifndef _FEDITOR_TEXTURE_MERGE_MODEL_H_
#define _FEDITOR_TEXTURE_MERGE_MODEL_H_
#include "Edit/AbstractModel.h"
#include "TypesDef.h"

namespace FEDITOR
{
	class Sprite;
	class Layer;
	class AbstractBlackboard;

	namespace TEXTURE_MERGE
	{
		class Blackboard;

		class Model : public AbstractModel
		{
		public:
			Model(const AbstractBlackboard* blackboard);
			virtual ~Model();

			virtual void handleEvent(const Event& event);

			Layer* getEditedLayer() const;

			void deleteTexture(Sprite* sprite);

		private:
			void initLayers();

			void initCoordsLinesSprite(Sprite* sprite);
			void initBgLinesSprite(Sprite* sprite);

			void addTexture(const std::string& filename);
			void saveTextures(const std::string& filename, IMG_TYPE format) const;

			void saveComposeInfo(const std::string& file, int height) const; 

		private:
			const Blackboard* m_blackboard;

			Sprite* m_bgLines;

			Layer* m_editedLayer;

			std::vector<Sprite*> m_textures;

		}; // Model
	}
}

#endif // _FEDITOR_TEXTURE_MERGE_MODEL_H_