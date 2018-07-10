#ifndef _WX_GUI_PASTE_SYMBOL_PHYSICS_OP_H_
#define _WX_GUI_PASTE_SYMBOL_PHYSICS_OP_H_

#include "PasteSymbolOP.h"

#include <Box2D/Box2D.h>

namespace wxgui
{
	class PhysicsPanelImpl;

	class PasteSymbolPhysicsOP : public PasteSymbolOP
	{
	public:
		PasteSymbolPhysicsOP(EditPanel* editPanel, MultiSpritesImpl* spritesImpl, 
			LibraryPanel* libraryPanel, PhysicsPanelImpl* physicsImpl, float* pScale = NULL);

		virtual bool onMouseLeftDown(int x, int y);

		void setStatic(bool bStatic) { m_bStatic = bStatic; }

	protected:
		bool m_bStatic;

	private:
		b2World* m_world;

		float* m_pScale;

	}; // PasteSymbolPhysicsOP
}

#endif // _WX_GUI_PASTE_SYMBOL_PHYSICS_OP_H_