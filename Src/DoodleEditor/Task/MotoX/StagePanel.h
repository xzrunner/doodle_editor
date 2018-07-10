#ifndef _DEDITOR_MOTOX_STAGE_PANEL_H_
#define _DEDITOR_MOTOX_STAGE_PANEL_H_

#include "ShapesPanelImpl.h"

#include <wxGUI/wxGUI.h>

namespace deditor
{
	namespace motox
	{
		class LibraryPanel;
		class Actor;

		class StagePanel : public wxgui::EditPanel, public wxgui::MultiSpritesImpl, 
			public ShapesPanelImpl, public wxgui::PhysicsPanelImpl
		{
		public:
			StagePanel(wxWindow* parent, LibraryPanel* libraryPanel);
			virtual ~StagePanel();

			//
			// wxgui::EditPanel interface
			//
			virtual void onKeyDown(wxKeyEvent& event);
			virtual void onKeyUp(wxKeyEvent& event);

			//
			// wxgui::MultiSpritesImpl interface
			//
			virtual void traverseSprites(IVisitor& visitor, 
				wxgui::TraverseType type = wxgui::e_allExisting,
				bool order = true) const;
			virtual void removeSprite(wxgui::ISprite* sprite);
			virtual void insertSprite(wxgui::ISprite* sprite);
			virtual void clear();

 			void insertSprite(int index, wxCoord x, wxCoord y);

			//
			// b2ContactListener interface
			//
			virtual void BeginContact(b2Contact* contact) {}
			virtual void EndContact(b2Contact* contact);
			virtual void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);
			virtual void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);

			//
			// wxgui::PhysicsPanelImpl interface
			//
			virtual void update(wxCommandEvent& event);
			virtual void drawPhysics();

			void setLayersMgr(wxgui::LayersMgrWidget* layersMgr) { 
				m_layersMgr = layersMgr; 
			}
			wxgui::LayersMgrWidget* getLayersMgr() { return m_layersMgr; }

			void insertActor(int index, wxCoord x, wxCoord y);
			Actor* getActor() { return m_actor; }

			void insertTemplate(int index, wxCoord x, wxCoord y);

			b2World* getWorld() { return wxgui::PhysicsPanelImpl::m_world; }
			b2World* getWorldReverse() { return m_worldReverse; }

			b2Body* getGround() { return m_ground; }
			b2Body* getGroundReverse() { return m_groundReverse; }

			const std::vector<wxgui::ISprite*>& getAllPhysics() const {
				return m_physicsSprites;
			}

		private:
			void loadGround();

		private:
			class DragSymbolTarget : public wxTextDropTarget
			{
			public:
				DragSymbolTarget(StagePanel* stagePanel);

				virtual bool OnDropText(wxCoord x, wxCoord y, const wxString& data);

			private:
				StagePanel* m_stagePanel;

			}; // DragSymbolTarget

		private:
			wxgui::LayersMgrWidget* m_layersMgr;

			std::vector<wxgui::ISprite*> m_physicsSprites;

			LibraryPanel* m_libraryPanel;

			Actor* m_actor;
			bool m_keyState[26];

			b2World* m_worldReverse;

			b2Body* m_ground;
			b2Body* m_groundReverse;

			std::vector<b2Body*> m_destoryCache;
			std::vector<std::pair<b2Body*, f2Vec2> > m_breakCache;

			friend class StageCanvas;

		}; // StagePanel 
	}
}

#endif // _DEDITOR_MOTOX_STAGE_PANEL_H_