#ifndef _WX_GUI_PHYSICS_PANEL_IMPL_H_
#define _WX_GUI_PHYSICS_PANEL_IMPL_H_

#include "Render/b2Render.h"

#include <Box2D/Box2D.h>
#include <Fruits2D/Fruits2D.h>
#include <wx/wx.h>

namespace wxgui
{
	class PhysicsPanelImpl : public b2ContactListener, public wxEvtHandler
	{
	public:
		PhysicsPanelImpl();
		virtual ~PhysicsPanelImpl();

		virtual void update(wxCommandEvent& event);

		virtual void drawPhysics();

		b2World* createWorld(const f2Vec2& gravity);

		void pause();

		b2World* getWorld() { return m_world; }

	protected:
		b2World* m_world;

	private:
		b2GLRender m_debugDraw;

		wxTimer* m_timer;
		bool m_isPaused;

	}; // PhysicsPanelImpl
}

#endif // _WX_GUI_PHYSICS_PANEL_IMPL_H_