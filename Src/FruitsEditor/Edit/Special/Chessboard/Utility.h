#ifndef _FEDITOR_CHESSBOARD_UTILITY_H_
#define _FEDITOR_CHESSBOARD_UTILITY_H_

namespace FEDITOR
{
	class Sprite;
	class Layer;

	namespace CHESSBOARD
	{
		class Blackboard;

		class Utility
		{
		public:
			static void fixSpritePos(Sprite* sprite, Layer* layer, Blackboard* blackboard);

		}; // Utility
	}
}

#endif // _FEDITOR_CHESSBOARD_UTILITY_H_