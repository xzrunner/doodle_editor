#include "Object.h"
#include "Frame/View/Backstage/ObjectPage.h"

using namespace GAME_FRUITS;

Object::Object(Scene* scene, const wxString& path, wxBitmap* img, int x, int y)
	: m_scene(scene), m_imgPath(path)
{
	static int count = 0;
	m_name = wxT("Object") + wxVariant(count++);
	m_bitmap = img;
	m_x = x;
	m_y = y;
	m_tabPage = NULL;
}

void Object::onPaint(wxDC& dc, const f2Vec2& origin) const
{
	dc.DrawBitmap(
		*m_bitmap, 
		origin.x + m_x - m_bitmap->GetWidth() * 0.5f, 
		origin.y + m_y - m_bitmap->GetHeight() * 0.5f
		);
}

void Object::onPaint(wxDC& dc, float scale) const
{
	const float width = m_bitmap->GetWidth() * scale,
		height = m_bitmap->GetHeight() * scale;

	dc.DrawBitmap(
		m_bitmap->ConvertToImage().Scale(width, height),
		800 * 0.5f * scale + m_x * scale - width * 0.5f,
		480 * 0.5f * scale + m_y * scale - height * 0.5f,
		true);
}

bool Object::isContain(int x, int y) const
{
	f2Vec2 pos(x, y);
	f2Vec2 leftlow(m_x - m_bitmap->GetWidth() * 0.5f, m_y - m_bitmap->GetHeight() * 0.5f);
	return f2Math::isPointInAABB(pos, leftlow, m_bitmap->GetWidth(), m_bitmap->GetHeight());
}

wxWindow* Object::createTabPage(wxNotebook* parent)
{
	if (!m_tabPage) m_tabPage = new VIEW::BACKSTAGE::ObjectPage(parent, this);
	return m_tabPage;
}