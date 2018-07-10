#include "FileIO.h"
#include "StagePanel.h"

#include <SOIL/SOIL.h>
#include <SOIL/stb_image_write.h>

using namespace deditor::automatic_merge;

void FileIO::load(std::ifstream& fin, StagePanel* stage, 
				  wxgui::LibraryPanel* libraryPanel)
{
	wxgui::SymbolMgr::Instance()->clear();
	wxgui::BitmapMgr::Instance()->clear();

	int width, height;
	fin >> width >> height;

	size_t size;
	fin >> size;
	for (size_t i = 0; i < size; ++i)
	{
		std::string filename = StringTools::getLine(fin);
		StringTools::getLine(fin);
		wxgui::ISymbol* symbol = wxgui::SymbolMgr::Instance()->getSymbol(filename);
		wxgui::ISprite* sprite = wxgui::SpriteFactory::create(symbol);
		stage->insertSprite(sprite);
	}

	libraryPanel->loadFromSymbolMgr(*wxgui::SymbolMgr::Instance());
}

void FileIO::store(const char* filename, StagePanel* stage, ToolbarPanel::IMG_TYPE type)
{
	storeImage(filename, stage, type);
	storePosInfo(filename, stage);
}

void FileIO::storeImage(const char* filename, StagePanel* stage, 
						ToolbarPanel::IMG_TYPE type)
{
	int width = stage->getWidth(),
		height = stage->getHeight();
	int channel = 4;
	if (type == ToolbarPanel::e_bmp || type == ToolbarPanel::e_jpg) 
		channel = 3;

	unsigned char* dst_data = (unsigned char*) malloc(channel * width * height);
	memset(dst_data, 0, channel * width * height);

	std::vector<wxgui::ISprite*> sprites;
	stage->traverseSprites(FetchAllVisitor<wxgui::ISprite>(sprites));
	for (size_t i = 0, n = sprites.size(); i < n; ++i)
	{
		wxgui::ISprite* sprite = sprites[i];
		const f2Vec2& center = sprite->getPosition();

		int w, h, c;
		unsigned char* src_data = SOIL_load_image(sprite->getSymbol().getFilepath().c_str(), &w, &h, &c, 0);
		for (size_t iRow = 0; iRow < h; ++iRow) {
			for (size_t iCol = 0; iCol < w; ++iCol) {
				const int baseFrom = (iRow * w + iCol) * c,
					baseTo = ((height - center.y - h * 0.5f + iRow) * width + center.x - w * 0.5f + iCol) * channel;
				for (size_t iCanel = 0; iCanel < channel; ++iCanel)
					dst_data[baseTo + iCanel] = src_data[baseFrom + iCanel];
			}
		}

		delete[] src_data;
	}

	wxString imgFile(filename);
	imgFile = wxgui::FilenameTools::getFilePathExceptExtension(imgFile);

	switch (type)
	{
	case ToolbarPanel::e_bmp:
		stbi_write_bmp((imgFile + ".bmp").c_str(), width, height, channel, dst_data);
		break;
	case ToolbarPanel::e_jpg:
		{
			wxgui::LibJpeg::ImageData data;
			data.width = width;
			data.height = height;
			data.pixels = dst_data;

			wxgui::LibJpeg::write_JPEG_file((imgFile + ".jpg").c_str(), 80, data);
		}
		break;
	case ToolbarPanel::e_png:
		stbi_write_png((imgFile + ".png").c_str(), width, height, channel, dst_data, 0);
		break;
	}

	free((void*)dst_data);
}

void FileIO::storePosInfo(const char* filename, StagePanel* stage)
{
	std::ofstream fout(filename);
	fout << stage->getWidth() << " " << stage->getHeight() << '\n';
	stage->traverseSprites(StoreSpriteVisitor(fout, stage->getHeight()));
	fout.close();
}

//////////////////////////////////////////////////////////////////////////
// class FileIO::StoreSpriteVisitor
//////////////////////////////////////////////////////////////////////////

FileIO::StoreSpriteVisitor::StoreSpriteVisitor(std::ofstream& fout, int height)
	: m_fout(fout)
{
	m_height = height;
}

FileIO::StoreSpriteVisitor::~StoreSpriteVisitor()
{
	m_fout << m_data.size() << '\n';
	for (size_t i = 0, n = m_data.size(); i < n; ++i)
	{
		wxgui::ImageSprite* sprite = m_data[i];

		const float width = sprite->getSymbol().getWidth(),
			height = sprite->getSymbol().getHeight();

		m_fout << sprite->getSymbol().getFilepath() << '\n'
			<< sprite->getPosition().x - width * 0.5f << " "
			<< m_height - sprite->getPosition().y - height * 0.5f << " "
			<< width << " " << height << '\n';
	}
}

void FileIO::StoreSpriteVisitor::visit(IObject* object, bool& bFetchNext)
{
	wxgui::ImageSprite* sprite = static_cast<wxgui::ImageSprite*>(object);
	if (sprite) m_data.push_back(sprite);

	bFetchNext = true;
}