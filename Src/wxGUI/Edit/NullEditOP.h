#ifndef _WX_GUI_NULL_EDIT_OP_H_
#define _WX_GUI_NULL_EDIT_OP_H_

#include "AbstractEditOP.h"

namespace wxgui
{
	class NullEditOP : public AbstractEditOP
	{
	public:
		NullEditOP(EditPanel* editPanel) : AbstractEditOP(editPanel) {}

	}; // NullEditOP
}

#endif // _WX_GUI_NULL_EDIT_OP_H_