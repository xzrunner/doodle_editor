#ifndef _WX_GUI_INTERFACE_SYMBOL_H_
#define _WX_GUI_INTERFACE_SYMBOL_H_

#include "Widgets/ListItem.h"
#include "Tools/ResourcesMgr.h"

namespace wxgui
{
	class ISymbol : public ListItem, public ISerializable
	{
	public:
		virtual ~ISymbol() {}

		//
		// IObject interface
		//	
		virtual ISymbol* clone() { return NULL; }

		virtual void reloadTexture() const = 0;
		virtual void draw() const = 0;
		virtual float getWidth() const = 0;
		virtual float getHeight() const = 0;

		bool loadFromFile(const wxString& filepath);

		const wxString& getFilepath() const { 
			return m_filepath; 
		}

	protected:
		virtual void loadResources() = 0;

	protected:
		wxString m_filepath;

	}; // ISymbol
}

#endif // _WX_GUI_INTERFACE_SYMBOL_H_