#ifndef _WX_GUI_PASTE_SYMBOL_RANDOM_OP_H_
#define _WX_GUI_PASTE_SYMBOL_RANDOM_OP_H_

#include "PasteSymbolOP.h"

#include "Widgets/PasteSymbolRandomWidget.h"

namespace wxgui
{
	class PasteSymbolRandomOP : public PasteSymbolOP
	{
	public:
		PasteSymbolRandomOP(EditPanel* editPanel, MultiSpritesImpl* spritesImpl, 
			LibraryPanel* libraryPanel, PasteSymbolRandomWidget* randomWidget);

		virtual bool onMouseLeftDown(int x, int y);
		virtual bool onMouseRightDown(int x, int y);

		virtual bool onDraw() const;

	private:
		void changeRandomValue();

	private:
		PasteSymbolRandomWidget* m_randomWidget;

		PasteSymbolRandomWidget::RandomValue m_randomValue;

	}; // PasteSymbolRandomOP
}

#endif // _WX_GUI_PASTE_SYMBOL_RANDOM_OP_H_