#ifndef _EASY_BUILDER_LIBGDX_BUILDER_H_
#define _EASY_BUILDER_LIBGDX_BUILDER_H_

#include "../CodePageBuilder.h"
#include "output/CodeGenerator.h"

#include <Fruits2D/Fruits2D.h>

namespace ebuilder
{
	class Actor;
	class CodeGenerator;
	class Behavior;

namespace libgdx
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
			CodeGenerator *gen, *importGen, *importStaticGen;

			SceneContent() {
				gen = new CodeGenerator;
				importGen = new CodeGenerator;
				importStaticGen = new CodeGenerator;
			}
			~SceneContent() {
				delete gen;
			}
		};

	private:
		void buildGamePage();
		void buildGameDesktopPage();
		void buildGameAndroidPage();

		void buildScenePage(const SceneItem& scene, Page* page);
		void buildActor(const Actor& actor, SceneContent& content);
		void buildBehaviors(const std::string& name, const std::vector<Behavior*>& behaviors, 
			SceneContent& content);
		void buildBehavior(const std::string& name, Behavior* behavior, SceneContent& content,
			std::vector<std::string>& actions);

		static void buildPosition(const Actor& actor, std::string& x, std::string& y);
		static void buildPosition(const f2Vec2& pos, std::string& x, std::string& y);

	private:
		static const int PAGE_OFFSET = 6;	// designer + Screen + Game + GameInstance + GameInstanceDesktop + GameInstanceAndroid

	}; // Builder

} // libgdx
} // ebuilder

#endif // _EASY_BUILDER_LIBGDX_BUILDER_H_