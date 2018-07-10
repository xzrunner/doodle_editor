#ifndef _FEDITOR_MONSTER_PREVIEW_H_
#define _FEDITOR_MONSTER_PREVIEW_H_
#include <Fruits2D/Fruits2D.h>

namespace FEDITOR
{
	class Sprite;
	class Layer;

	namespace MONSTER
	{
		class Blackboard;

		class Preview
		{
		public:
			Preview(Blackboard* blackboard);

			void load(Layer* layer);

			void start();
//			void stop();
			void step();

		private:
			void drawView() const;
			void drawTotal() const;

			float getYBase(float length) const;

		private:
			static const float LEFTMOST;
			static const float COL_WIDTH;

		private:
			Blackboard* m_blackboard;

			long m_start;

			std::vector<Sprite*> m_sprites;

		}; // Preview
	}
}

#endif // _FEDITOR_MONSTER_PREVIEW_H_