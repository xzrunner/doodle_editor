#ifndef _EASY_BUILDER_SCENE_PROPERTY_SETTING_H_
#define _EASY_BUILDER_SCENE_PROPERTY_SETTING_H_

#include <wxGUI/wxGUI.h>

namespace ebuilder
{
	class SceneItem;
	class ScenesPage;

	class ScenePropertySetting : public wxgui::IPropertySetting
	{
	public:
		ScenePropertySetting(SceneItem* scene, ScenesPage* scenesPage);

		virtual void updatePanel(wxgui::PropertySettingPanel* panel);

		virtual void onPropertyGridChange(const wxString& name, const wxAny& value);
		virtual void updatePropertyGrid(wxgui::PropertySettingPanel* panel);
		virtual void enablePropertyGrid(wxgui::PropertySettingPanel* panel, bool bEnable);

	private:
		void updateSceneName(const wxString& name);

	private:
		class UpdateNameVisitor : public IVisitor
		{
		public:
			UpdateNameVisitor(SceneItem* scene) 
				: m_scene(scene) {}

			virtual void visit(IObject* object, bool& bFetchNext);

		private:
			SceneItem* m_scene;

		}; // UpdateNameVisitor

	private:
		SceneItem* m_scene;

		ScenesPage* m_scenesPage;

	}; // ScenePropertySetting
}

#endif // _EASY_BUILDER_SCENE_PROPERTY_SETTING_H_