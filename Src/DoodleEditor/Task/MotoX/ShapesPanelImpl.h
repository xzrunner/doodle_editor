#ifndef _DEDITOR_MOTOX_SHAPES_PANEL_IMPL_H_
#define _DEDITOR_MOTOX_SHAPES_PANEL_IMPL_H_

#include <wxGUI/wxGUI.h>

namespace deditor
{
	namespace motox
	{
		class TrackChain;

		class ShapesPanelImpl : public wxgui::MultiShapesImpl
		{
		public:
			ShapesPanelImpl(wxWindow* wnd);
			virtual ~ShapesPanelImpl();

			//
			// wxgui::MultiShapesImpl interface
			//
			virtual void traverseShapes(IVisitor& visitor, 
				wxgui::TraverseType type = wxgui::e_allExisting) const;
			virtual void removeShape(wxgui::IShape* shape);
			virtual void insertShape(wxgui::IShape* shape);
			virtual void clear();

			void setWorld(b2World* world, b2World* worldReverse) { 
				m_world = world;
				m_worldReverse = worldReverse;
			}

			void setTracksFriction(float friction);

			const std::vector<TrackChain*>& getTrackChains() const { return m_chains; }

			void getTracksRegion(float& leftmost, float& rightmost) const;

		private:
			std::vector<TrackChain*> m_chains;

			std::vector<wxgui::PolygonShape*> m_polys;

			b2World *m_world, *m_worldReverse;

			friend class TrackChainIOCMPT;

		}; // ShapesPanelImpl
	}
}

#endif // _DEDITOR_MOTOX_SHAPES_PANEL_IMPL_H_