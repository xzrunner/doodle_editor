#ifndef _FEDITOR_MONSTER_UTILITY_H_
#define _FEDITOR_MONSTER_UTILITY_H_

namespace FEDITOR
{
	class Sprite;
	class Layer;

	namespace MONSTER
	{
		class Blackboard;

		class Utility
		{
		public:
			static void fixSpritePos(Sprite* sprite, Layer* layer, Blackboard* blackboard);

		private:
			static void eraseSamePosUnderground(Layer* layer, float d0, float d1, Sprite* except);

		}; // Utility
	}
}

#endif // _FEDITOR_MONSTER_UTILITY_H_