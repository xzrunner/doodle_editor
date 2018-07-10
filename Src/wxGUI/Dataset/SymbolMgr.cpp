#include "SymbolMgr.h"
#include "SymbolFactory.h"
#include "ISymbol.h"

using namespace wxgui;

SymbolMgr* SymbolMgr::m_instance = NULL;

SymbolMgr::SymbolMgr()
{
}

SymbolMgr::~SymbolMgr()
{
	clear();
}

SymbolMgr* SymbolMgr::Instance()
{
	if (!m_instance)
	{
		m_instance = new SymbolMgr();
	}
	return m_instance;
}

ISymbol* SymbolMgr::getSymbol(const wxString& filepath)
{
	std::map<wxString, ISymbol*>::iterator itr = m_symbols.find(filepath);
	if (itr == m_symbols.end())
	{
		ISymbol* symbol = SymbolFactory::create(filepath);
		bool isLoaded = symbol->loadFromFile(filepath);
		if (isLoaded)
		{
			m_symbols.insert(std::make_pair(filepath, symbol));
			return symbol;
		}
		else
		{
			delete symbol;
			return NULL;
		}
	}
	else
	{
		return itr->second;
	}
}

void SymbolMgr::clear()
{
	std::map<wxString, ISymbol*>::iterator itr = m_symbols.begin();
	for ( ; itr != m_symbols.end(); ++itr)
		delete itr->second;
	m_symbols.clear();
}

void SymbolMgr::traverse(IVisitor& visitor) const
{
	std::map<wxString, ISymbol*>::const_iterator itr = m_symbols.begin();
	for ( ; itr != m_symbols.end(); ++itr)
	{
		bool hasNext;
		visitor.visit(itr->second, hasNext);
		if (!hasNext) break;
	}
}

