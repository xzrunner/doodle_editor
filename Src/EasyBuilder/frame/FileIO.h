#ifndef _EASY_BUILDER_FILE_IO_H_
#define _EASY_BUILDER_FILE_IO_H_

#include <wx/wx.h>
#include <json/json.h>

namespace ebuilder
{
	class LibraryPanel;
	class Scene;
	class SceneItem;
	class Actor;
	class Behavior;

	class FileIO
	{
	public:
		static void load(const wxString& filepath);
		static void store(const wxString& filepath);

	private:
		static void loadGame(const Json::Value& gameValue);
		static SceneItem* loadScene(const Json::Value& sceneValue,
			std::vector<std::pair<Behavior*, wxString> >& buffer);
		static Actor* loadActor(const Json::Value& actorValue,
			std::vector<std::pair<Behavior*, wxString> >& buffer);
		static Behavior* loadBehavior(const Json::Value& behaviorValue,
			Actor* actor, std::vector<std::pair<Behavior*, wxString> >& buffer);
		static void loadBehaviorsValue(
			const std::vector<std::pair<Behavior*, wxString> >& buffer);

		static void storeGame(Json::Value& value);
		static Json::Value store(Scene* scene);
		static Json::Value store(Actor* actor);
		static Json::Value store(Behavior* behavior);
		static void store(Json::Value& value, Behavior* behavior);

	}; // FileIO
}

#endif // _EASY_BUILDER_FILE_IO_H_