#ifndef _WX_GUI_SYMBOL_FACTORY_H_
#define _WX_GUI_SYMBOL_FACTORY_H_

#include <wx/wx.h>

namespace wxgui
{
	class ISymbol;

	class SymbolFactory
	{
	public:
		static ISymbol* create(const wxString& filepath);

	}; // SymbolFactory
}

#endif // _WX_GUI_SYMBOL_FACTORY_H_