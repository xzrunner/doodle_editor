#include "FileIO.h"

#include "dataset/Game.h"
#include "dataset/Scene.h"
#include "dataset/Actor.h"
#include "view/Context.h"
#include "view/LibraryPanel.h"
#include "view/ScenesPage.h"
#include "view/SceneItem.h"
#include "view/ActorsPage.h"
#include "view/ActorItem.h"
#include "behaviors/BehaviorFactory.h"
#include "behaviors/ChangeImage.h"
#include "behaviors/ChangeScene.h"
#include "behaviors/ScaleSize.h"
#include "behaviors/MouseButton.h"
#include "behaviors/Move.h"
#include "behaviors/Rotate.h"

using namespace ebuilder;

void FileIO::load(const wxString& filepath)
{
	Json::Value value;
	Json::Reader reader;
	std::ifstream fin(filepath.fn_str());
	reader.parse(fin, value);
	fin.close();

	loadGame(value);

	std::vector<std::pair<Behavior*, wxString> > buffer;

	LibraryPanel* library = Context::Instance()->library;

	int i = 0;
	Json::Value sceneValue = value["scene"][i++];
	wxgui::LibraryList* list = library->getSceneList();
	while (!sceneValue.isNull()) {
		SceneItem* scene = loadScene(sceneValue, buffer);
		list->insert(scene);
		sceneValue = value["scene"][i++];
	}

	list->SetSelection(0);
	list->onListSelected(wxCommandEvent(list->GetSelection()));
	if (i > 2) library->getScenePage()->enableDelBtn();

	library->loadFromSymbolMgr(*wxgui::SymbolMgr::Instance());

	loadBehaviorsValue(buffer);
}

void FileIO::store(const wxString& filepath)
{
	Json::Value value;

	storeGame(value);

	std::vector<SceneItem*> scenes;
	Context::Instance()->library->getSceneList()->traverse(
		FetchAllVisitor<SceneItem>(scenes));

	for (size_t i = 0, n = scenes.size(); i < n; ++i)
	{
		value["scene"][i] = store(scenes[i]->getScene());
	}

	Json::StyledStreamWriter writer;
	std::ofstream fout(filepath.fn_str());
	writer.write(fout, value);
	fout.close();
}

void FileIO::loadGame(const Json::Value& gameValue)
{
	Game::NAME = gameValue["name"].asString();

	Game::WIDTH = gameValue["width"].asInt();
	Game::HEIGHT = gameValue["height"].asInt();
}

SceneItem* FileIO::loadScene(const Json::Value& sceneValue,
							 std::vector<std::pair<Behavior*, wxString> >& buffer)
{
	Scene* scene = new Scene;
	SceneItem* item = new SceneItem(scene);

	item->setName(sceneValue["name"].asString());

	scene->m_tag = sceneValue["tag"].asString();

	wxColor color;
	color.Set(sceneValue["color"].asString());
	scene->m_color = color;
	
	int i = 0;
	Json::Value actorValue = sceneValue["actor"][i++];
	while (!actorValue.isNull()) {
		Actor* actor = loadActor(actorValue, buffer);
		Context::Instance()->library->addActor(actor);
		scene->insertActor(actor);

		actorValue = sceneValue["actor"][i++];
	}

	item->refreshThumbnail();

	return item;
}

Actor* FileIO::loadActor(const Json::Value& actorValue,
						 std::vector<std::pair<Behavior*, wxString> >& buffer)
{
	wxString filepath = actorValue["filepath"].asString();
	wxgui::ImageSymbol* symbol = dynamic_cast<wxgui::ImageSymbol*>
		(wxgui::SymbolMgr::Instance()->getSymbol(filepath));
	assert(symbol);

	Actor* actor = new Actor(symbol);

	actor->m_name = actorValue["name"].asString();

	actor->m_tag = actorValue["tag"].asString();

	f2Vec2 position;
	position.x = actorValue["position"]["x"].asDouble();
	position.y = actorValue["position"]["y"].asDouble();

	float angle = actorValue["angle"].asDouble();

	actor->setTransform(position, angle);

	actor->setScale(actorValue["scale"].asDouble());

	actor->setMirror(actorValue["x mirror"].asBool(),
		actorValue["y mirror"].asBool());

	actor->m_isBg = actorValue["isBg"].asBool();

	int i = 0;
	Json::Value behaviorValue = actorValue["behavior"][i++];
	while (!behaviorValue.isNull()) {
		Behavior* behavior = loadBehavior(behaviorValue, actor, buffer);
		actor->addBehavior(behavior);

		behaviorValue = actorValue["behavior"][i++];
	}

	return actor;
}

Behavior* FileIO::loadBehavior(const Json::Value& behaviorValue,
							   Actor* actor, std::vector<std::pair<Behavior*, wxString> >& buffer)
{
	std::string name = behaviorValue["name"].asString();
	if (name == MOUSE_BUTTON_NAME)
	{
		MouseButton* mouseButton = static_cast<MouseButton*>
			(BehaviorFactory::createBehavior(e_MouseButton, actor));

		mouseButton->bPress = behaviorValue["press"].asBool();

		int i = 0;
		Json::Value doValue = behaviorValue["do"][i++];
		while (!doValue.isNull()) {
			Behavior* behavior = loadBehavior(doValue, actor, buffer);
			mouseButton->satisfies.push_back(behavior);

			doValue = behaviorValue["do"][i++];
		}

		return mouseButton;
	}
	else if (name == CHANGE_IMAGE_NAME)
	{
		ChangeImage* changeImage = static_cast<ChangeImage*>
			(BehaviorFactory::createBehavior(e_ChangeImage, actor));
		std::string path = behaviorValue["image path"].asString();
		wxgui::ImageSymbol* symbol = dynamic_cast<wxgui::ImageSymbol*>
			(wxgui::SymbolMgr::Instance()->getSymbol(path));
		buffer.push_back(std::make_pair(changeImage, path));
		return changeImage;
	}
	else if (name == CHANGE_SCENE_NAME)
	{
		ChangeScene* changeScene = static_cast<ChangeScene*>
			(BehaviorFactory::createBehavior(e_ChangeScene, actor));
		buffer.push_back(std::make_pair(changeScene, behaviorValue["scene name"].asString()));
		return changeScene;
	}
	else if (name == SCALE_SIZE_NAME)
	{
		ScaleSize* scaleSize = static_cast<ScaleSize*>
			(BehaviorFactory::createBehavior(e_ScaleSize, actor));
		scaleSize->val = (behaviorValue["scale"].asDouble() * 100 + 0.5f) * 0.01f;
		return scaleSize;
	}
	else if (name == MOVE_NAME)
	{
		Move* move = static_cast<Move*>
			(BehaviorFactory::createBehavior(e_Move, actor));
		move->start.x = behaviorValue["start"]["x"].asDouble();
		move->start.y = behaviorValue["start"]["y"].asDouble();
		move->end.x = behaviorValue["end"]["x"].asDouble();
		move->end.y = behaviorValue["end"]["y"].asDouble();
		move->speed = behaviorValue["speed"].asDouble();
		return move;
	}
	else if (name == ROTATE_NAME)
	{
		Rotate* rotate = static_cast<Rotate*>
			(BehaviorFactory::createBehavior(e_Rotate, actor));
		rotate->start = behaviorValue["start"].asDouble();
		rotate->end = behaviorValue["end"].asDouble();
		rotate->speed = behaviorValue["speed"].asDouble();
		return rotate;
	}
	else
	{
		return NULL;
	}
}

void FileIO::loadBehaviorsValue(const std::vector<std::pair<Behavior*, wxString> >& buffer)
{
	LibraryPanel* library = Context::Instance()->library;

	for (size_t i = 0, n = buffer.size(); i < n; ++i)
	{
		Behavior* behavior = buffer[i].first;
		switch (behavior->type())
		{
		case e_ChangeImage:
			{
				ChangeImage* changeImage = static_cast<ChangeImage*>(behavior);

				int index = 0;
				wxgui::ISymbol* symbol = library->getMediaList()->getSymbol(index);
				while (symbol)
				{
					if (symbol->getFilepath() == buffer[i].second)
					{
						changeImage->selected = symbol;
						break;
					}

					symbol = library->getMediaList()->getSymbol(++index);
				}
			}
			break;
		case e_ChangeScene:
			{
				ChangeScene* changeScene = static_cast<ChangeScene*>(behavior);

				int index = 0;
				wxgui::ISymbol* symbol = library->getSceneList()->getSymbol(index);
				while (symbol)
				{
					if (symbol->getName() == buffer[i].second)
					{
						changeScene->selected = symbol;
						break;
					}

					symbol = library->getSceneList()->getSymbol(++index);
				}
			}
			break;
		}
	}
}

void FileIO::storeGame(Json::Value& value)
{
	value["name"] = Game::NAME.ToStdString();

	value["width"] = Game::WIDTH;
	value["height"] = Game::HEIGHT;
}

Json::Value FileIO::store(Scene* scene)
{
	Json::Value value;

	value["name"] = scene->m_name.ToStdString();

	value["tag"] = scene->m_tag.ToStdString();

	wxString str = scene->m_color.GetAsString(wxC2S_HTML_SYNTAX);
	value["color"] = str.ToStdString();

	std::vector<Actor*> actors = scene->getActors();
	for (size_t i = 0, n = actors.size(); i < n; ++i)
	{
		value["actor"][i] = store(actors[i]);
	}

	return value;
}

Json::Value FileIO::store(Actor* actor)
{
	Json::Value value;

	value["filepath"] = actor->getSymbol().getFilepath().ToStdString();

	value["name"] = actor->m_name.ToStdString();

	value["tag"] = actor->m_tag.ToStdString();

	value["position"]["x"] = actor->getPosition().x;
	value["position"]["y"] = actor->getPosition().y;

	value["angle"] = actor->getAngle();

	value["scale"] = actor->getScale();

	bool xMirror, yMirror;
	actor->getMirror(xMirror, yMirror);
	value["x mirror"] = xMirror;
	value["y mirror"] = yMirror;

	value["isBg"] = actor->m_isBg;

	const std::vector<Behavior*>& behaviors = actor->getBehaviors();
	for (size_t i = 0, n = behaviors.size(); i < n; ++i)
	{
		value["behavior"][i] = store(behaviors[i]);
	} 

	return value;
}

Json::Value FileIO::store(Behavior* behavior)
{
	Json::Value value;

	value["name"] = behavior->getName().ToStdString();

	switch (behavior->type())
	{
	case e_MouseButton:
		{
			MouseButton* mouseButton = static_cast<MouseButton*>(behavior);

			value["press"] = mouseButton->bPress;

			const std::vector<Behavior*>& behaviors = mouseButton->satisfies;
			for (size_t i = 0, n = behaviors.size(); i < n; ++i)
				store(value["do"][i], behaviors[i]);
		}
		break;
	default:
		store(value, behavior);
	}

	return value;
}

void FileIO::store(Json::Value& value, Behavior* behavior)
{
	value["name"] = behavior->getName().ToStdString();
	switch (behavior->type())
	{
	case e_ChangeImage:
		{
			ChangeImage* changeImage = static_cast<ChangeImage*>(behavior);
			value["image path"] = changeImage->selected->getFilepath().ToStdString();
		}
		break;
	case e_ChangeScene:
		{
			ChangeScene* changeScene = static_cast<ChangeScene*>(behavior);
			value["scene name"] = changeScene->selected->getName().ToStdString();
		}
		break;
	case e_ScaleSize:
		{
			ScaleSize* scaleSize = static_cast<ScaleSize*>(behavior);
			value["scale"] = scaleSize->val;
		}
		break;
	case e_Move:
		{
			Move* move = static_cast<Move*>(behavior);
			value["start"]["x"] = move->start.x;
			value["start"]["y"] = move->start.y;
			value["end"]["x"] = move->end.x;
			value["end"]["y"] = move->end.y;
			value["speed"] = move->speed;
		}
		break;
	case e_Rotate:
		{
			Rotate* rotate = static_cast<Rotate*>(behavior);
			value["start"] = rotate->start;
			value["end"] = rotate->end;
			value["speed"] = rotate->speed;
		}
		break;
	}
}