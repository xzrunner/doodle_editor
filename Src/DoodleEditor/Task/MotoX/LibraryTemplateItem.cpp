#include "LibraryTemplateItem.h"
#include "TEFileAdapter.h"

using namespace deditor::motox;

LibraryTemplateItem::LibraryTemplateItem()
{
	static int id = 0;
	m_name = wxT("template") + wxVariant(id++);
}

float LibraryTemplateItem::getWidth() const
{
	return 0;
}

float LibraryTemplateItem::getHeight() const
{
	return 0;
}

void LibraryTemplateItem::computeCenter()
{
	m_center.set(0, 0);
	for (size_t i = 0, n = m_sprites.size(); i < n; ++i)
		m_center += m_sprites[i]->getPosition();
	m_center /= m_sprites.size();
}

void LibraryTemplateItem::loadResources()
{
	TEFileAdapter adapter;
	adapter.resolve(m_filepath);

	for (size_t j = 0, m = adapter.m_data.size(); j < m; ++j)
	{
		const TEFileAdapter::Entry& entry = adapter.m_data[j];

		wxgui::ISymbol* symbol = wxgui::SymbolMgr::Instance()->getSymbol(entry.filepath);
		wxgui::ISprite* sprite = wxgui::SpriteFactory::create(symbol);
		sprite->setTransform(entry.pos, entry.angle);
		sprite->setScale(entry.scale);

		m_sprites.push_back(sprite);
	}
	computeCenter();
}