#ifndef _WX_GUI_LAYER_H_
#define _WX_GUI_LAYER_H_

#include <wx/wx.h>
#include <Fruits2D/Fruits2D.h>

namespace wxgui
{	
	class ISprite;
	class IShape;

	class Layer : public IObject
 	{
 	public:
 		Layer();
 		~Layer();

		//
		// IObject interface
		//
		virtual IObject* clone() { return NULL; }

		const wxString& getName() const { return m_name; }
		void setName(const wxString& name);

		// use IVisitor if has other implementation
		const std::vector<ISprite*>& getSprites() const { return m_sprites; }
		const std::vector<IShape*>& getShapes() const { return m_shapes; }

		void traverseSprites(IVisitor& visitor) const;
		void traverseShapes(IVisitor& visitor) const;

		void insert(ISprite* shape);
		void remove(ISprite* shape);

		void insert(IShape* sprite);
		void remove(IShape* sprite);

 		void clear();
 
 	private:
		wxString m_name;

 		std::vector<ISprite*> m_sprites;
 		std::vector<IShape*> m_shapes;
 
 	}; // Layer
}

#endif // _WX_GUI_LAYER_H_