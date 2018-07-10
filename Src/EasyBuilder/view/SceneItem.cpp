#include "SceneItem.h"

#include "dataset/Actor.h"
#include "dataset/Scene.h"
#include "dataset/Game.h"

using namespace ebuilder;

const float SceneItem::THUMBNAIL_SCALE = 0.15f;

SceneItem::SceneItem(Scene* scene)
	: m_scene(scene)
{
	m_name = m_scene->m_name;

	m_bitmap = new wxgui::Bitmap(
		new wxBitmap(
		Game::WIDTH * THUMBNAIL_SCALE, 
		Game::HEIGHT * THUMBNAIL_SCALE)
		);
}

SceneItem::~SceneItem()
{
	delete m_scene;
}

SceneItem* SceneItem::clone()
{
	return NULL;
}

void SceneItem::loadFromTextFile(std::ifstream& fin)
{
}

void SceneItem::storeToTextFile(std::ofstream& fout) const
{
}

void SceneItem::reloadTexture() const
{
}

void SceneItem::draw() const
{
}

float SceneItem::getWidth() const
{
	return 0;
}

float SceneItem::getHeight() const
{
	return 0;
}

void SceneItem::insertActor(Actor* actor)
{
	m_scene->insertActor(actor);
	refreshThumbnail();
}

void SceneItem::removeActor(Actor* actor)
{
	m_scene->removeActor(actor);
	refreshThumbnail();
}

const wxString& SceneItem::getName() const
{
	return m_name;
}

void SceneItem::setName(const wxString& name)
{
	m_name = name;
	m_scene->m_name = name;
}

void SceneItem::refreshThumbnail()
{
	wxMemoryDC memDC;
	memDC.SelectObject(const_cast<wxBitmap&>(*m_bitmap->getBitmap()));

	memDC.SetBackground(wxBrush(*wxBLACK));
//	memDC.SetBackground(wxBrush(m_scene->m_color/**wxRED*/));
	memDC.Clear();

	const std::vector<Actor*>& actors = m_scene->getActors();
	for (size_t i = 0, n = actors.size(); i < n; ++i)
	{
		Actor* actor = actors[i];
		const wxBitmap* bitmap = actor->getSymbol().getBitmap()->getBitmap();

		const float width = actor->getSymbol().getWidth() * THUMBNAIL_SCALE,
			height = actor->getSymbol().getHeight() * THUMBNAIL_SCALE;
		const float hWidth = width * 0.5f,
			hHeight = height * 0.5f;

		float xMin, yMin;
		xMin = yMin = FLOAT_MAX;

		f2Vec2 p = f2Math::rotateVector(f2Vec2(-hWidth, -hHeight), actor->getAngle());
		if (p.x < xMin) xMin = p.x;
		if (p.y < yMin) yMin = p.y;

		p = f2Math::rotateVector(f2Vec2(-hWidth, hHeight), actor->getAngle());
		if (p.x < xMin) xMin = p.x;
		if (p.y < yMin) yMin = p.y;

		p = f2Math::rotateVector(f2Vec2(hWidth, -hHeight), actor->getAngle());
		if (p.x < xMin) xMin = p.x;
		if (p.y < yMin) yMin = p.y;

		p = f2Math::rotateVector(f2Vec2(hWidth, hHeight), actor->getAngle());
		if (p.x < xMin) xMin = p.x;
		if (p.y < yMin) yMin = p.y;

		wxPoint pos;
		pos.x = Game::WIDTH * 0.5f * THUMBNAIL_SCALE + actor->getPosition().x * THUMBNAIL_SCALE + xMin;
		pos.y = Game::HEIGHT * 0.5f * THUMBNAIL_SCALE - actor->getPosition().y * THUMBNAIL_SCALE + yMin;

		memDC.DrawBitmap(
			bitmap->ConvertToImage().Scale(width, height).Rotate(actor->getAngle(), wxPoint(0, 0)),
			pos,
			true);
	}

	memDC.SelectObject(wxNullBitmap);
}
