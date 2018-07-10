#include "ActorItem.h"

#include "dataset/Actor.h"

using namespace ebuilder;

ActorItem::ActorItem(Actor* actor)
	: m_actor(actor)
{
	m_name = actor->m_name;

	m_filepath = m_actor->getSymbol().getFilepath();
	const wxgui::Bitmap* init = wxgui::BitmapMgr::Instance()->getItem(m_filepath);
	if (m_bitmap != init) delete m_bitmap;
	m_bitmap = const_cast<wxgui::Bitmap*>(init);
}

void ActorItem::loadFromTextFile(std::ifstream& fin)
{

}

void ActorItem::storeToTextFile(std::ofstream& fout) const
{

}

void ActorItem::reloadTexture() const
{
}

void ActorItem::draw() const
{
//	m_actor->getSymbol().draw();
}

float ActorItem::getWidth() const
{
	return 0;
}

float ActorItem::getHeight() const
{
	return 0;
}

void ActorItem::loadResources()
{
}