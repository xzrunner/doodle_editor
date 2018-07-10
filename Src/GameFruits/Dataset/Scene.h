#ifndef _GAME_FRUITS_SCENE_H_
#define _GAME_FRUITS_SCENE_H_
#include <Fruits2D/Fruits2D.h>
#include "Dataset/InterimData.h"
#include <wx/wx.h>

namespace GAME_FRUITS
{
	class Object;
	class InterimData;

	class Scene
	{
	public:
		Scene(int width, int height);
		~Scene();

		void storeToInterimData(InterimData& interim) const;
		void loadFromInterimData(const InterimData& interim);

		void addImage(const wxString& path, int x, int y);
		void deleteObject(Object* obj);
		Object* queryByPoint(int x, int y);
		const std::vector<Object*>& getAllObjects() const;

		void onPaint(wxDC& dc, const f2Vec2& origin) const;
		void onPaint(wxDC& dc, float scale) const;

		const wxString& getName() const;
		void setName(const wxString& name);

		const wxColour& getColor() const;
		void setColor(const wxColour& color);

	private:
		void clear();

		bool isButton(const Object* object) const;
		void loadButton(const Object* object, InterimData::Button& btn) const;

	private:
		wxString m_name;
		int m_width, m_height;

		wxColour m_color;

		std::map<wxString, wxBitmap*> m_mapPathToImg;
		std::vector<Object*> m_objects;

	}; // Scene

	inline const wxString& Scene::getName() const
	{
		return m_name;
	}

	inline void Scene::setName(const wxString& name)
	{
		m_name = name;
	}

	inline const wxColour& Scene::getColor() const
	{
		return m_color;
	}

	inline void Scene::setColor(const wxColour& color)
	{
		m_color = color;
	}
}

#endif // _GAME_FRUITS_SCENE_H_
