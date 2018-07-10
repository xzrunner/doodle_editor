#include "LibraryActorItem.h"

using namespace deditor::motox;

LibraryActorItem::LibraryActorItem()
{
	static int id = 0;
	m_name = wxT("actor") + wxVariant(id++);
}

void LibraryActorItem::loadFromTextFile(std::ifstream& fin)
{
	for (size_t i = 0; i < PARTS_COUNT; ++i)
	{
		m_parts[i].path = StringTools::getLine(fin);

		std::string strLine = StringTools::getLine(fin);
		std::stringstream ss(strLine);

		ss >> m_parts[i].pos >> m_parts[i].angle;
	}
	for (size_t i = 0; i < JOINTS_TYPE_COUNT; ++i)
	{
		fin >> m_joints[i] >> m_joints[i].anchor;
	}
}

void LibraryActorItem::storeToTextFile(std::ofstream& fout) const
{
	for (size_t i = 0; i < PARTS_COUNT; ++i)
	{
		fout << m_parts[i].path << '\n';
		fout << m_parts[i].pos << " " << m_parts[i].angle << '\n';
	}
	for (size_t i = 0; i < JOINTS_TYPE_COUNT; ++i)
	{
		fout << m_joints[i] << " " << m_joints[i].anchor << '\n';
	}
}

void LibraryActorItem::reloadTexture() const
{

}

void LibraryActorItem::draw() const
{

}

float LibraryActorItem::getWidth() const
{
	return 0;
}

float LibraryActorItem::getHeight() const
{
	return 0;
}

void LibraryActorItem::setLocation(const f2Vec2& pos)
{
	for (size_t i = 0; i < JOINTS_TYPE_COUNT; ++i)
	{
		m_joints[i].anchor += pos;
	}
}

void LibraryActorItem::loadResources()
{
	std::ifstream fin(m_filepath.fn_str());
	loadFromTextFile(fin);
	fin.close();
}

//////////////////////////////////////////////////////////////////////////
// class LibraryActorItem::PartDef
//////////////////////////////////////////////////////////////////////////

wxgui::ISprite* LibraryActorItem::PartDef::loadBodySprite() const
{
	if (path.IsEmpty()) return NULL;

	wxgui::ISymbol* symbol = wxgui::SymbolMgr::Instance()->getSymbol(path);

	wxgui::ISprite* sprite = wxgui::SpriteFactory::create(symbol);
	sprite->setTransform(pos, angle);
	sprite->loadBodyFromFile();

	return sprite;
}