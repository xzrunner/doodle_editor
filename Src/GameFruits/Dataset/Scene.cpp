#include "Scene.h"
#include "Dataset/Object.h"
#include "Frame/Regulars/MousePress.h"
#include "Frame/Regulars/ChangeScene.h"

using namespace GAME_FRUITS;

Scene::Scene(int width, int height)
{
	static int count = 0;
	m_name = wxT("Scene") + wxVariant(count++);

	m_width = width;
	m_height = height;

	m_color = *wxBLACK;
}

Scene::~Scene()
{
	clear();
}

void Scene::storeToInterimData(InterimData& interim) const
{
	interim.m_sceneName = m_name;

	interim.m_objects.clear();
	interim.m_buttons.clear();
	for (size_t i = 0, n = m_objects.size(); i < n; ++i)
	{
		Object* object = m_objects[i];

		InterimData::Entry entry;
		entry.path = object->getImgPath();
		entry.name = object->getName();
		object->getPosition(entry.x, entry.y);

		if (isButton(object)) 
		{
			InterimData::Button btn;
			btn.entry = entry;
			loadButton(object, btn);
			interim.m_buttons.push_back(btn);
		}
		else 
			interim.m_objects.push_back(entry);
	}
}

void Scene::loadFromInterimData(const InterimData& interim)
{
	clear();
	m_objects.reserve(interim.m_objects.size());
	for (size_t i = 0, n = interim.m_objects.size(); i < n; ++i)
	{
		InterimData::Entry entry = interim.m_objects[i];
		addImage(entry.path, entry.x, entry.y);
	}
}

void Scene::addImage(const wxString& path, int x, int y)
{
	wxBitmap* bitmap = NULL;
	std::map<wxString, wxBitmap*>::iterator itr = m_mapPathToImg.find(path);
	if (itr == m_mapPathToImg.end())
	{
		wxImage image;
		image.LoadFile(path);
		bitmap = new wxBitmap(image);
		m_mapPathToImg.insert(std::make_pair(path, bitmap));
	}
	else
	{
		bitmap = itr->second;
	}
	m_objects.push_back(new Object(this, path, bitmap, x, y));
}

void Scene::deleteObject(Object* obj)
{
	std::vector<Object*>::iterator itr = m_objects.begin();
	for ( ; itr != m_objects.end(); ++itr)
	{
		if (*itr == obj)
		{
			m_objects.erase(itr);
			break;
		}
	}
}

Object* Scene::queryByPoint(int x, int y)
{
	for (int i = m_objects.size() - 1; i >= 0; --i)
	{
		Object* obj = m_objects[i];
		if (m_objects[i]->isContain(x, y))
			return obj;
	}
	return NULL;
}

const std::vector<Object*>& Scene::getAllObjects() const
{
	return m_objects;
}

void Scene::onPaint(wxDC& dc, const f2Vec2& origin) const
{
	dc.SetBrush(wxBrush(m_color));
	dc.DrawRectangle(
		origin.x - 800 * 0.5f, 
		origin.y - 480 * 0.5f,
		800,
		480
		);

	for (size_t i = 0, n = m_objects.size(); i < n; ++i)
		m_objects[i]->onPaint(dc, origin);
}

void Scene::onPaint(wxDC& dc, float scale) const
{
 	// method 0
   	dc.SetBackground(wxBrush(m_color));	
   	dc.Clear();

// 	// method 1
// 	dc.SetBrush(wxBrush(m_color));
// 	dc.DrawRectangle(0, 0, 800 * scale, 480 * scale);

 	for (size_t i = 0, n = m_objects.size(); i < n; ++i)
 		m_objects[i]->onPaint(dc, scale);
}

void Scene::clear()
{
	std::map<wxString, wxBitmap*>::iterator itr = m_mapPathToImg.begin();
	for ( ; itr != m_mapPathToImg.end(); ++itr)
		delete itr->second;
	m_mapPathToImg.clear();

	for_each(m_objects.begin(), m_objects.end(), DeletePointerFunctor<Object>());
}

bool Scene::isButton(const Object* object) const
{
	const std::vector<RegularListItem*>& regulars = object->getAllRegulars();
	for (size_t i = 0, n = regulars.size(); i < n; ++i)
	{
		REGULAR::MousePress* mousePress = dynamic_cast<REGULAR::MousePress*>(regulars[i]);
		if (mousePress) return true;
	}
	return false;
}

void Scene::loadButton(const Object* object, InterimData::Button& btn) const
{
	const std::vector<RegularListItem*>& regulars = object->getAllRegulars();
	for (size_t i = 0, n = regulars.size(); i < n; ++i)
	{
		REGULAR::MousePress* mousePress = dynamic_cast<REGULAR::MousePress*>(regulars[i]);
		if (mousePress) 
		{
			const std::vector<RegularListItem*>& regulars = mousePress->getAllRegulars(true);
			for (size_t j = 0, m = regulars.size(); j < m; ++j)
			{
				REGULAR::ChangeScene* changeScene = dynamic_cast<REGULAR::ChangeScene*>(regulars[j]);
				if (changeScene) 
				{
					btn.toSceneName = changeScene->getSelectedScene()->getName();
					return;
				}
			}
		}
	}
}