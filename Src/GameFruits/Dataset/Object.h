#ifndef _GAME_FRUITS_OBJECT_H_
#define _GAME_FRUITS_OBJECT_H_
#include <Fruits2D/Fruits2D.h>
#include <wx/wx.h>
#include <wx/notebook.h>

namespace GAME_FRUITS
{
	class Scene;
	class RegularListItem;

	class Object
	{
	public:
		Object(Scene* scene, const wxString& path, wxBitmap* img, int x, int y);

		void onPaint(wxDC& dc, const f2Vec2& origin) const;
		void onPaint(wxDC& dc, float scale) const;

		bool isContain(int x, int y) const;

		void translate(int dx, int dy);

		const wxString& getImgPath() const;
		wxBitmap* getBitmap() const;

		const wxString& getName() const;
		void setName(const wxString& name);

		void getPosition(int& x, int& y) const;
		void setPosition(int x, int y);

		void getSize(int& width, int& height) const;
		void setSize(int width, int height);

		Scene* getScene() const;

		void addRegular(RegularListItem* regular);
		const std::vector<RegularListItem*>& getAllRegulars() const;

		wxWindow* createTabPage(wxNotebook* parent);

	private:
		wxString m_name;

		wxString m_imgPath;
		wxBitmap* m_bitmap;
		int m_x, m_y;

		Scene* m_scene;

		std::vector<RegularListItem*> m_regulars;

		wxWindow* m_tabPage;

	}; // Object

	inline void Object::translate(int dx, int dy)
	{
		m_x += dx;
		m_y += dy;
	}

	inline const wxString& Object::getImgPath() const
	{
		return m_imgPath;
	}

	inline wxBitmap* Object::getBitmap() const
	{
		return m_bitmap;
	}

	inline const wxString& Object::getName() const
	{
		return m_name;
	}

	inline void Object::setName(const wxString& name)
	{
		m_name = name;
	}

	inline void Object::getPosition(int& x, int& y) const
	{
		x = m_x;
		y = m_y;
	}

	inline void Object::setPosition(int x, int y)
	{
		m_x = x;
		m_y = y;
	}

	inline void Object::getSize(int& width, int& height) const
	{
		width = m_bitmap->GetWidth();
		height = m_bitmap->GetHeight();
	}

	inline void Object::setSize(int width, int height)
	{
		wxImage img = m_bitmap->ConvertToImage();
		img.Rescale(width, height);
		delete m_bitmap;
		m_bitmap = new wxBitmap(img);
	}

	inline Scene* Object::getScene() const
	{
		return m_scene;
	}

	inline void Object::addRegular(RegularListItem* regular)
	{
		m_regulars.push_back(regular);
	}

	inline const std::vector<RegularListItem*>& Object::getAllRegulars() const
	{
		return m_regulars;
	}
}

#endif // _GAME_FRUITS_OBJECT_H_