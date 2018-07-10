#ifndef _EASY_BUILDER_PREVIEW_CHANGE_SCENE_H_
#define _EASY_BUILDER_PREVIEW_CHANGE_SCENE_H_

#include "Behavior.h"

namespace ebuilder
{	
	namespace preview
	{
		class Panel;
		class Scene;

		class ChangeScene : public Behavior
		{
		public:
			ChangeScene(Panel* panel, Scene* scene);
			virtual ~ChangeScene();

			virtual void trigger();

		private:
			Panel* m_panel;

			Scene* m_scene;

		}; // ChangeScene
	}
}

#endif // _EASY_BUILDER_PREVIEW_CHANGE_SCENE_H_