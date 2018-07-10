#ifndef _WX_GUI_SYMBOL_MANAGER_H_
#define _WX_GUI_SYMBOL_MANAGER_H_

#include <wx/wx.h>
#include <Fruits2D/Fruits2D.h>

namespace wxgui
{
	class ISymbol;

	class SymbolMgr
	{
	public:
		static SymbolMgr* Instance();

		ISymbol* getSymbol(const wxString& filepath);

		void clear();

		void traverse(IVisitor& visitor) const;

	private:
		SymbolMgr();
		~SymbolMgr();

	private:
		static SymbolMgr* m_instance;

		std::map<wxString, ISymbol*> m_symbols;

	}; // SymbolMgr
}

#endif // _WX_GUI_SYMBOL_MANAGER_H_