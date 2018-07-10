#ifndef _EASY_BUILDER_LOVE2D_BUILDER_H_
#define _EASY_BUILDER_LOVE2D_BUILDER_H_

#include "../CodePageBuilder.h"
#include "output/CodeGenerator.h"

#include <Fruits2D/Fruits2D.h>

namespace ebuilder
{
	class SceneItem;
	class Actor;
	class CodeGenerator;
	class Behavior;

namespace love2d
{
	class Page;

	class Builder : public CodePageBuilder
	{
	public:
		Builder(wxNotebook* notebook);

		virtual void loadPages();

		virtual void updatePage(const SceneItem& scene);

		virtual void insertPage(const SceneItem& scene);

		virtual void removePage(const SceneItem& scene);

	private:
		struct SceneContent
		{
			CodeGenerator *gen;
			CodeGenerator *genImages, *genActors, *genButtons;
			CodeGenerator *genRequire;

			std::string name;

			SceneContent() {
				gen = new CodeGenerator;
				genImages = new CodeGenerator;
				genActors = new CodeGenerator;
				genButtons = new CodeGenerator;
				genRequire = new CodeGenerator;
			}
			~SceneContent() {
				delete gen;
			}
		};

	private:
		void buildMainPage();

		void buildScenePage(const SceneItem& scene, Page* page);
		void buildActor(const Actor& actor, SceneContent& content);
		void buildBehavior(const std::string& name, const std::string& actionFunc,
			Behavior* behavior, SceneContent& content);
		std::string buildImage(const std::string& filepath, SceneContent& content);

		static void transCoords(const f2Vec2& pos, std::string& x, std::string& y);
		static void transScale(const Actor& actor, std::string& sx, std::string& sy);

	private:
		static const int PAGE_OFFSET = 3;	// designer + main + button

	}; // Builder
	
} // love2d
} // ebuilder

#endif // _EASY_BUILDER_LOVE2D_BUILDER_H_