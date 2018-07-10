#ifndef _DEDITOR_MEDELING_PREVIEW_PANEL_H_
#define _DEDITOR_MEDELING_PREVIEW_PANEL_H_

#include <wxGUI/wxGUI.h>

namespace deditor
{
	namespace modeling
	{
		class StagePanel;
		class BodyData;

		class PreviewPanel : public wxgui::EditPanel, 
			public wxgui::PhysicsPanelImpl
		{
		public:
			PreviewPanel(wxWindow* parent, StagePanel* stagePanel,
				wxgui::LibraryPanel* libraryPanel);

		private:
			void createGround();

		private:
			class LoadBodyVisitor : public IVisitor
			{
			public:
				LoadBodyVisitor(b2World* world, std::map<BodyData*, b2Body*>& transBody);
				virtual void visit(IObject* object, bool& bFetchNext);

			private:
				b2World* m_world;

				std::map<BodyData*, b2Body*>& m_transBody;

			}; // LoadBodyVisitor

			class LoadJointVisitor : public IVisitor
			{
			public:
				LoadJointVisitor(b2World* world, const std::map<BodyData*, b2Body*>& transBody);

				virtual void visit(IObject* object, bool& bFetchNext);

			private:
				b2World* m_world;

				const std::map<BodyData*, b2Body*>& m_transBody;

			}; // LoadJointVisitor

		private:
			b2Body* m_ground;

		}; // PreviewPanel
	}
}

#endif // _DEDITOR_MEDELING_PREVIEW_PANEL_H_