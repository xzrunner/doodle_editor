#include "FileIO.h"
#include "StagePanel.h"

#include <Frame/defs.h>

using namespace deditor::combination;

void FileIO::load(const wxgui::CombinationFileAdapter& adapter, 
				  StagePanel* stage, wxgui::LibraryPanel* libraryPanel)
{
	wxgui::SymbolMgr::Instance()->clear();
	wxgui::BitmapMgr::Instance()->clear();

	for (size_t i = 0, n = adapter.m_data.size(); i < n; ++i)
	{
		const wxgui::CombinationFileAdapter::Entry& entry = adapter.m_data[i];

		wxgui::ISprite* sprite = NULL;
		wxgui::ISymbol* symbol = wxgui::SymbolMgr::Instance()->getSymbol(entry.filepath);
		sprite = wxgui::SpriteFactory::create(symbol);

		sprite->setTransform(entry.pos, entry.angle);
		sprite->setScale(entry.scale);
		sprite->setMirror(entry.xMirror, entry.yMirror);

		stage->insertSprite(sprite);
		sprite->release();
	}

	libraryPanel->loadFromSymbolMgr(*wxgui::SymbolMgr::Instance());
	stage->resetCanvas();
}

void FileIO::store(std::ofstream& fout, StagePanel* stage)
{
	std::vector<wxgui::ISprite*> sprites;
	stage->traverseSprites(FetchAllVisitor<wxgui::ISprite>(sprites));

	f2AABB aabb;
	for (size_t i = 0, n = sprites.size(); i < n; ++i)
	{
		std::vector<f2Vec2> vertices;
		sprites[i]->getBounding()->getBoundPos(vertices);
		for (size_t j = 0, m = vertices.size(); j < m; ++j)
			aabb.combine(vertices[j]);
	}
	f2Vec2 offset(-aabb.xCenter(), -aabb.yCenter());

	fout << sprites.size() << '\n';
	for (size_t i = 0, n = sprites.size(); i < n; ++i)
	{
		wxgui::ISprite* sprite = sprites[i];

		fout << sprite->getSymbol().getFilepath() << '\n';

		bool xMirror, yMirror;
		sprite->getMirror(xMirror, yMirror);
		fout << sprite->getPosition() + offset << " " 
			<< sprite->getAngle() << " " 
			<< sprite->getScale() << " " 
			<< xMirror << " " << yMirror 
			<< '\n';
	}
	fout.close();
}
