#ifndef _FEDITOR_TEST_RENDERING_RENDER_H_
#define _FEDITOR_TEST_RENDERING_RENDER_H_
#include <Fruits2D/Fruits2D.h>

namespace FEDITOR
{
	class Sprite;
	class AbstractView;

	namespace TEST_RENDERING
	{
		class Blackboard;

		class Render
		{
		public:
			static void immediateMode(const std::vector<Sprite*>& sprites, AbstractView* view);
			static void bindOneTime(const std::vector<Sprite*>& sprites, AbstractView* view);
			static void bindOneTime_strip(const std::vector<Sprite*>& sprites, AbstractView* view);
			static void bindOneTime_strip_death(const std::vector<Sprite*>& sprites, AbstractView* view);
			static void drawArrays(const std::vector<Sprite*>& sprites, AbstractView* view);
			static void drawElements(const std::vector<Sprite*>& sprites, AbstractView* view);
			static void drawElements_interleave(const std::vector<Sprite*>& sprites, AbstractView* view);
			static void drawRangeElements(const std::vector<Sprite*>& sprites, AbstractView* view);
			static void displayList(const std::vector<Sprite*>& sprites, AbstractView* view);
			static void vbo(const std::vector<Sprite*>& sprites, AbstractView* view);

		private:
			static void setVSync(int interval = 1);
			static bool isExtensionSupported(char* szTargetExtension);

		public:
			static Blackboard* m_bb;

		}; // Render
	}
}

#endif // _FEDITOR_TEST_RENDERING_RENDER_H_