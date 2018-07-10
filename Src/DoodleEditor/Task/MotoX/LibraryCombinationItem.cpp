#include "LibraryCombinationItem.h"

#include "Frame/defs.h"

using namespace deditor;
using namespace deditor::motox;

LibraryCombinationItem::LibraryCombinationItem()
{
	static int id = 0;
	m_name = wxT("×éºÏ") + wxVariant(id++);
}

void LibraryCombinationItem::loadFromTextFile(std::ifstream& fin)
{

}

void LibraryCombinationItem::storeToTextFile(std::ofstream& fout) const
{

}

void LibraryCombinationItem::reloadTexture() const
{

}

void LibraryCombinationItem::draw() const
{
	
}

float LibraryCombinationItem::getWidth() const
{
	return 0;
}

float LibraryCombinationItem::getHeight() const
{
	return 0;
}

//void LibraryCombinationItem::createBitmap()
//{
// 	f2AABB aabb;
// 	for (size_t i = 0, n = m_sprites.size(); i < n; ++i)
// 	{
// 		m_sprites[i]->getBounding()->
// 	}
// 
// 
// 	wxMemoryDC memDC;
// 	m_bitmap->SetWidth(100);
// 	m_bitmap->SetHeight(100);
// 
// 	memDC.SelectObject(m_bitmap);
// 
// //	memDC.SetBackground(wxBrush());
// 	memDC.Clear();
// 
// 	for (size_t i = 0, n = m_sprites.size(); i < n; ++i)
// 	{
// 		memDC.DrawBitmap();
// 	}
// 
// 	memDC.SelectObject(wxNullBitmap);
//}

void LibraryCombinationItem::loadResources()
{
	wxgui::CombinationFileAdapter adapter;
	adapter.load(m_filepath.c_str());

	for (size_t i = 0, n = adapter.m_data.size(); i < n; ++i)
	{
		wxgui::ISprite* sprite = NULL;

		const wxgui::CombinationFileAdapter::Entry& entry = adapter.m_data[i];
		wxgui::ISymbol* symbol = wxgui::SymbolMgr::Instance()->getSymbol(entry.filepath);
		sprite = wxgui::SpriteFactory::create(symbol);

		sprite->setTransform(entry.pos, entry.angle);
		sprite->setScale(entry.scale);
		sprite->setMirror(entry.xMirror, entry.yMirror);

		m_sprites.push_back(sprite);
	}

	setCenter();
}

void LibraryCombinationItem::setCenter()
{
	m_center.set(0, 0);
	for (size_t i = 0, n = m_sprites.size(); i < n; ++i)
		m_center += m_sprites[i]->getPosition();
	if (!m_sprites.empty())
		m_center /= m_sprites.size();
}