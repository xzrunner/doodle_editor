#ifndef _WX_GUI_PASTE_SYMBOL_PHYSICS_RANDOM_OP_H_
#define _WX_GUI_PASTE_SYMBOL_PHYSICS_RANDOM_OP_H_

#include "PasteSymbolPhysicsOP.h"

#include "Widgets/PasteSymbolRandomWidget.h"

namespace wxgui
{
	class PasteSymbolPhysicsRandomOP : public PasteSymbolPhysicsOP
	{
	public:
		PasteSymbolPhysicsRandomOP(EditPanel* editPanel, MultiSpritesImpl* spritesImpl, 
			LibraryPanel* libraryPanel, PhysicsPanelImpl* physicsImpl, PasteSymbolRandomWidget* randomWidget);

		virtual bool onMouseLeftDown(int x, int y);
		virtual bool onMouseRightDown(int x, int y);

		virtual bool onDraw() const;

	private:
		void changeRandomValue();

	private:
		PasteSymbolRandomWidget* m_randomWidget;

		PasteSymbolRandomWidget::RandomValue m_randomValue;

	}; // PasteSymbolPhysicsRandomOP
}

#endif // _WX_GUI_PASTE_SYMBOL_PHYSICS_RANDOM_OP_H_