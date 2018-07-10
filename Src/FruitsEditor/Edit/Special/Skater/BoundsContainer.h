#ifndef _FEDITOR_SKATER_BOUNDS_CONTAINER_H_
#define _FEDITOR_SKATER_BOUNDS_CONTAINER_H_
#include <Fruits2D/Fruits2D.h>

namespace FEDITOR
{
	class LoopsFileAdapter;

	namespace SKATER
	{
		class BoundsContainer
		{
		public:
			~BoundsContainer();

			LoopsFileAdapter* insert(const std::string& filename);
			LoopsFileAdapter* query(const std::string& filename) const;

		private:
			std::map<std::string, LoopsFileAdapter*> m_mapNameToBound;

		}; // BoundsContainer
	}
}

#endif // _FEDITOR_SKATER_BOUNDS_CONTAINER_H_