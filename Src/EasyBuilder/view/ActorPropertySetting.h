#ifndef _EASY_BUILDER_ACTOR_PROPERTY_SETTING_H_
#define _EASY_BUILDER_ACTOR_PROPERTY_SETTING_H_

#include <wxGUI/wxGUI.h>

namespace ebuilder
{
	class Actor;

	class ActorPropertySetting : public wxgui::IPropertySetting
	{
	public:
		ActorPropertySetting(Actor* actor, wxgui::LibraryList* actorList);

		virtual void updatePanel(wxgui::PropertySettingPanel* panel);

		virtual void onPropertyGridChange(const wxString& name, const wxAny& value);
		virtual void updatePropertyGrid(wxgui::PropertySettingPanel* panel);
		virtual void enablePropertyGrid(wxgui::PropertySettingPanel* panel, bool bEnable);

	private:
		void updateActorName(const wxString& name);

	private:
		class UpdateNameVisitor : public IVisitor
		{
		public:
			UpdateNameVisitor(Actor* actor) 
				: m_actor(actor) {}

			virtual void visit(IObject* object, bool& bFetchNext);

		private:
			Actor* m_actor;

		}; // UpdateNameVisitor

	private:
		Actor* m_actor;

		wxgui::LibraryList* m_actorList;

	}; // ActorPropertySetting
}

#endif // _EASY_BUILDER_ACTOR_PROPERTY_SETTING_H_