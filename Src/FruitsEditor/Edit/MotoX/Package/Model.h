#ifndef _FEDITOR_MOTOX_PACKAGE_MODEL_H_
#define _FEDITOR_MOTOX_PACKAGE_MODEL_H_
#include "Edit/AbstractModel.h"

namespace FEDITOR
{
	class AbstractBlackboard;

	namespace MOTOX
	{
		namespace PACKAGE
		{
			class Blackboard;

			class Model : public AbstractModel
			{
			public:
				Model(const AbstractBlackboard* blackboard);
				virtual ~Model();

				virtual void handleEvent(const Event& event);

			private:
				struct Region
				{
					int left, top;
					int width, height;
				};

			private:
				void packTrackChain(const std::string& src, const std::string& dst);

				void packActor(const std::string& src, const std::string& dst);
				void buildTexturesLookupTable(std::ifstream& fin, std::map<std::string, Region*>& lookup);
				void storeActorToFile(std::ifstream& src, std::ofstream& dst, std::map<std::string, Region*>& lookup);

			private:
				const Blackboard* m_blackboard;

			}; // Model
		}
	}
}

#endif // _FEDITOR_MOTOX_PACKAGE_MODEL_H_