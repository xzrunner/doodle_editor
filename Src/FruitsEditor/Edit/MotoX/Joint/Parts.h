#ifndef _FEDITOR_MOTOX_JOINT_PARTS_H_
#define _FEDITOR_MOTOX_JOINT_PARTS_H_
#include "../ActorDefs.h"
#include <Fruits2D/Fruits2D.h>

namespace FEDITOR
{
	class Sprite;
	class Layer;
	class ActorMotionAdapter;

	namespace MOTOX
	{
		namespace JOINT
		{
			class Parts : public ISerializable
			{
			public:
				Parts();

				//
				// ISerializable interface
				//
				virtual void loadFromTextFile(std::ifstream& fin);
				virtual void storeToTextFile(std::ofstream& fout) const;

				void loadFromFileAdapter(const ActorMotionAdapter& adapter);
				
				void initSprites(Layer* layer);

				void loadPartTypeFromFile(size_t type, const std::string& filename);

				Sprite* getPart(size_t id);

				void setAlive(bool isAlive);

			private:
				void loadPartFromTextFile(std::ifstream& fin, size_t part);
				void loadPartFromFileAdapter();
				void storePartToTextFile(std::ofstream& fout, size_t part) const;

				void loadPartFromFile(size_t part, const std::string& filename);
				void setCollisionFilter(size_t part);

			private:
				static const size_t PARTS_COUNT = PLAYER_PARTS_COUNT + MOTORBIKE_PARTS_COUNT;

				static const int PARTS_ORDER[PARTS_COUNT];

			private:
				Sprite* m_parts[PARTS_COUNT];

			}; // Parts

			inline Sprite* Parts::getPart(size_t id)
			{
				if (id >= 0 && id < PARTS_COUNT)
					return m_parts[id];
				else
					return NULL;
			}
		}
	}
}

#endif // _FEDITOR_MOTOX_JOINT_PARTS_H_