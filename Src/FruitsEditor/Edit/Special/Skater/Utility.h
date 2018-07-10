#ifndef _FEDITOR_SKATER_UTILITY_H_
#define _FEDITOR_SKATER_UTILITY_H_

namespace FEDITOR
{
	class Sprite;

	namespace SKATER
	{
		class BoundsContainer;

		class Utility
		{
		public:
			static void addSpriteBound(Sprite* sprite, const BoundsContainer& m_bounds);

		}; // Utility
	}
}

#endif // _FEDITOR_SKATER_UTILITY_H_