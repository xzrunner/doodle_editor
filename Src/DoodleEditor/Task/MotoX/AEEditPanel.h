#ifndef _DEDITOR_MOTOX_ACTOR_EDIT_PANEL_H_
#define _DEDITOR_MOTOX_ACTOR_EDIT_PANEL_H_

#include "AEParts.h"
#include "AEJoints.h"
#include "AECanvas.h"

#include <wxGUI/wxGUI.h>

namespace deditor
{
	namespace motox
	{
		class AEEditPanel : public wxgui::EditPanel, public wxgui::MultiSpritesImpl, 
			public wxgui::PhysicsPanelImpl
		{
		public:
			AEEditPanel(wxWindow* parent, wxgui::LibraryPanel* libraryPanel,
				LibraryActorItem& params);
			virtual ~AEEditPanel();

			//
			// wxgui::MultiSpritesImpl interface
			//
			virtual void traverseSprites(IVisitor& visitor, 
				wxgui::TraverseType type = wxgui::e_allExisting,
				bool order = true) const;
			virtual void removeSprite(wxgui::ISprite* sprite) {}
			virtual void insertSprite(wxgui::ISprite* sprite) {}
			virtual void clear();

			//
			// wxgui::PhysicsPanelImpl interface
			//
			virtual void update(wxCommandEvent& event);

			void insertSprite(int index, wxCoord x, wxCoord y);

			AEParts& getParts() { return m_parts; }
			AEJoints& getJoints() { return m_joints; }

			void loadDataFromFile(std::ifstream& fin);
			void storeDataToFile(std::ofstream& fout) const;

			b2World* getWorld() { return m_world; }
			b2Body* getGround() { return m_ground ? m_ground->getBody() : NULL; }

			const LibraryActorItem& getActorItem() const { return m_params; }

		private:
			void initBackground();

		private:
			class DragSymbolTarget : public wxTextDropTarget
			{
			public:
				DragSymbolTarget(AEEditPanel* panelImpl);

				virtual bool OnDropText(wxCoord x, wxCoord y, const wxString& data);

			private:
				AEEditPanel* m_panelImpl;

			}; // DragSymbolTarget

			class UpdateVisitor : public IVisitor
			{
			public:
				virtual void visit(IObject* object, bool& bFetchNext);
			}; // UpdateVisitor

		private:
			wxgui::IBody* m_ground;

			AEParts m_parts;
			AEJoints m_joints;

			wxgui::LibraryPanel* m_libraryPanel;

			LibraryActorItem& m_params;

		}; // AEEditPanel
	}
}

#endif // _DEDITOR_MOTOX_ACTOR_EDIT_PANEL_H_