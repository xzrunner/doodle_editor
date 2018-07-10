#include "PackageFileIOUtils.h"

using namespace deditor;
using namespace deditor::motox;

PackageFileIOUtils::PackageFileIOUtils(wxgui::MultiSpritesImpl* spritesImpl,
									   const automatic_merge::FileAdapter& merged, float gridWidth)
	: m_spritesImpl(spritesImpl)
	, m_merged(merged)
	, m_gridWidth(gridWidth)
	, m_leftmost(FLOAT_MAX)
	, m_rightmost(-FLOAT_MAX)
{
}

PackageFileIOUtils::PackageFileIOUtils(wxgui::MultiSpritesImpl* spritesImpl, 
									   const automatic_merge::FileAdapter& merged, 
									   float gridWidth, float leftmost, float rightmost)
	: m_spritesImpl(spritesImpl)
	, m_merged(merged)
	, m_gridWidth(gridWidth)
	, m_leftmost(leftmost)
	, m_rightmost(rightmost)
{
}


void PackageFileIOUtils::storeToFileSingleLayer(const wxString& filepath, 
												const std::vector<wxgui::ISprite*>& sprites)
{
	initAllDataRegion(sprites);

	Grids internal, intersect;
	initGrids(sprites, internal, intersect);

	std::ofstream fout(filepath.fn_str(), std::ios::out | std::ios::binary);
	storeHeader(fout);
	storeData(fout, internal, intersect);
	fout.close();
}

void PackageFileIOUtils::loadFromFileSingleLayer(const wxString& filepath)
{
	std::ifstream fin(filepath.fn_str(), std::ios::in | std::ios::binary);

	loadHeader(fin);

	Grids internal, intersect;
	loadData(fin, internal, intersect);

	fin.close();

	addToStagePanel(internal, intersect);
}

void PackageFileIOUtils::storeToFileMultiLayers(const wxString& filepath, 
												const std::vector<wxgui::Layer*>& layers)
{
	initAllDataRegion(layers);

	std::ofstream fout(filepath.fn_str(), std::ios::out | std::ios::binary);
	storeHeader(fout);
	storeData(fout, layers);
	fout.close();
}

void PackageFileIOUtils::loadFromFileMultiLayers(const wxString& filepath)
{
	std::ifstream fin(filepath.fn_str(), std::ios::in | std::ios::binary);

	loadHeader(fin);
	
	std::vector<Grids> internals, intersects;
	loadData(fin, internals, intersects);

	fin.close();

	for (size_t i = 0, n = internals.size(); i < n; ++i)
		addToStagePanel(internals[i], intersects[i]);
}

void PackageFileIOUtils::initAllDataRegion(const std::vector<wxgui::ISprite*>& sprites)
{
	if (m_leftmost != FLOAT_MAX || m_rightmost != -FLOAT_MAX)
		return;

	dataRegionCombine(sprites);
}

void PackageFileIOUtils::initAllDataRegion(const std::vector<wxgui::Layer*>& layers)
{
	if (m_leftmost != FLOAT_MAX || m_rightmost != -FLOAT_MAX)
		return;

	for (size_t i = 0, n = layers.size(); i < n; ++i)
		dataRegionCombine(layers[i]->getSprites());
}

void PackageFileIOUtils::dataRegionCombine(const std::vector<wxgui::ISprite*>& sprites)
{
	for (size_t i = 0, n = sprites.size(); i < n; ++i)
	{
		AbstractBV* bounding = sprites[i]->getBounding();
		std::vector<f2Vec2> pos;
		bounding->getBoundPos(pos);
		for (size_t j = 0, m = pos.size(); j < m; ++j)
		{
			if (pos[j].x < m_leftmost) m_leftmost = pos[j].x;
			if (pos[j].x > m_rightmost) m_rightmost = pos[j].x;
		}
	}
}

void PackageFileIOUtils::initGrids(const std::vector<wxgui::ISprite*>& sprites,
								   Grids& internal, Grids& intersect)
{
	const size_t gridSize = std::ceil((m_rightmost - m_leftmost) / m_gridWidth);
	internal.resize(gridSize);
	if (gridSize > 1)
		intersect.resize(gridSize - 1);

	for (size_t i = 0, n = sprites.size(); i < n; ++i)
	{
		wxgui::ImageSprite* sprite = dynamic_cast<wxgui::ImageSprite*>(sprites[i]);
		if (!sprite) continue;

		AbstractBV* bounding = sprite->getBounding();
		std::vector<f2Vec2> pos;
		bounding->getBoundPos(pos);

		float left = FLOAT_MAX,
			right = -FLOAT_MAX;
		for (size_t j = 0, m = pos.size(); j < m; ++j)
		{
			if (pos[j].x < left) left = pos[j].x;
			if (pos[j].x > right) right = pos[j].x;
		}

		const int iLeft = (left - m_leftmost) / m_gridWidth,
			iRight = (right - m_leftmost) / m_gridWidth;
		if (iLeft == iRight)
		{
			internal[iLeft].push_back(sprite);
		}
		else
		{
			assert(iLeft + 1 == iRight);
			intersect[iLeft].push_back(sprite);
		}
	}
}

void PackageFileIOUtils::storeHeader(std::ofstream& fout)
{
	fout.write(reinterpret_cast<const char*>(&m_leftmost), sizeof(float));
	fout.write(reinterpret_cast<const char*>(&m_gridWidth), sizeof(float));

}

void PackageFileIOUtils::storeData(std::ofstream& fout, const Grids& internal, 
								   const Grids& intersect)
{
	size_t gridSize = internal.size();
	if (gridSize >= 256)
		throw std::exception("PackageFileIOUtils::storeData gridSize over 256");
	fout.write(reinterpret_cast<const char*>(&gridSize), sizeof(byte));
	for (size_t i = 0; i < gridSize; ++i)
//		storeData(fout, internal[i]);
		storeDataCompress(fout, internal[i]);

	if (gridSize > 1)
	{
		for (size_t i = 0, n = gridSize - 1; i < n; ++i)
//			storeData(fout, intersect[i]);
			storeDataCompress(fout, intersect[i]);
	}
}

void PackageFileIOUtils::storeData(std::ofstream& fout, const std::vector<wxgui::Layer*>& layers)
{
	size_t size = layers.size();
	if (size >= 256)
		throw std::exception("PackageFileIOUtils::storeData layerSize over 256");
	fout.write(reinterpret_cast<const char*>(&size), sizeof(byte));
	for (size_t i = 0; i < size; ++i)
	{
		Grids internal, intersect;
		initGrids(layers[i]->getSprites(), internal, intersect);

		storeData(fout, internal, intersect);
	}
}

void PackageFileIOUtils::storeData(std::ofstream& fout, const std::vector<wxgui::ISprite*>& sprites)
{
	size_t spriteSize = sprites.size();
	fout.write(reinterpret_cast<const char*>(&spriteSize), sizeof(size_t));
	for (size_t i = 0, n = sprites.size(); i < n; ++i)
	{
		wxgui::ISprite* sprite = sprites[i];

		int id = -1;
		for (size_t j = 0, m = m_merged.m_data.size(); j < m; ++j)
		{
			if (m_merged.m_data[j].filepath == sprite->getSymbol().getFilepath())
			{
				id = j;
				break;
			}
		}
		assert(id != -1);

		fout.write(reinterpret_cast<const char*>(&id), sizeof(int));

		const f2Vec2& pos = sprite->getPosition();
		fout.write(reinterpret_cast<const char*>(&pos.x), sizeof(float));
		fout.write(reinterpret_cast<const char*>(&pos.y), sizeof(float));

		float angle = sprite->getAngle();
		fout.write(reinterpret_cast<const char*>(&angle), sizeof(float));

		float scale = sprite->getScale();
		fout.write(reinterpret_cast<const char*>(&scale), sizeof(float));

		bool xMirror, yMirror;
		sprite->getMirror(xMirror, yMirror);
		unsigned int type = 0;
		if (xMirror) 
			type |= SPRITE_X_MIRROR;
		if (yMirror) 
			type |= SPRITE_Y_MIRROR;		
		fout.write(reinterpret_cast<const char*>(&type), sizeof(unsigned int));
	}
}

void PackageFileIOUtils::storeDataCompress(std::ofstream& fout, const std::vector<wxgui::ISprite*>& sprites)
{
	size_t spriteSize = sprites.size();
	if (spriteSize >= 256)
		throw std::exception("PackageFileIOUtils::storeDataCompress spriteSize over 256");
	fout.write(reinterpret_cast<const char*>(&spriteSize), sizeof(byte));

	if (spriteSize == 0) 
		return;
	else if (spriteSize == 1)
	{
		wxgui::ISprite* sprite = sprites[0];

		int id = -1;
		for (size_t j = 0, m = m_merged.m_data.size(); j < m; ++j)
		{
			if (m_merged.m_data[j].filepath == sprite->getSymbol().getFilepath())
			{
				id = j;
				break;
			}
		}
		assert(id != -1);
		if (id >= 256)
			throw std::exception("PackageFileIOUtils::storeDataCompress id over 256");
		fout.write(reinterpret_cast<const char*>(&id), sizeof(byte));

		const f2Vec2& pos = sprite->getPosition();
		fout.write(reinterpret_cast<const char*>(&pos.x), sizeof(float));
		fout.write(reinterpret_cast<const char*>(&pos.y), sizeof(float));

		int angle = compressAngle(sprite->getAngle());
		assert(angle >= 0 && angle <= 255);
		fout.write(reinterpret_cast<const char*>(&angle), sizeof(byte));

		unsigned int type = compressType(sprite);
		fout.write(reinterpret_cast<const char*>(&type), sizeof(byte));

		if (sprite->getScale() != 1)
		{
			float scale = sprite->getScale();
			fout.write(reinterpret_cast<const char*>(&scale), sizeof(float));
		}
	}
	else
	{
		float xMin = FLOAT_MAX, xMax = -FLOAT_MAX,
			yMin = FLOAT_MAX, yMax = -FLOAT_MAX,
			sMin = FLOAT_MAX, sMax = -FLOAT_MAX;
		for (size_t i = 0, n = sprites.size(); i < n; ++i)
		{
			const f2Vec2& pos = sprites[i]->getPosition();
			if (pos.x < xMin) xMin = pos.x;
			if (pos.x > xMax) xMax = pos.x;
			if (pos.y < yMin) yMin = pos.y;
			if (pos.y > yMax) yMax = pos.y;

			const float scale = sprites[i]->getScale();
			if (scale < sMin) sMin = scale;
			if (scale > sMax) sMax = scale;
		}
		const float dx = (xMax - xMin) / 255.0f,
			dy = (yMax - yMin) / 255.0f,
			ds = (sMax - sMin) / 255.0f;
		fout.write(reinterpret_cast<const char*>(&xMin), sizeof(float));
		fout.write(reinterpret_cast<const char*>(&dx), sizeof(float));
		fout.write(reinterpret_cast<const char*>(&yMin), sizeof(float));
		fout.write(reinterpret_cast<const char*>(&dy), sizeof(float));
		fout.write(reinterpret_cast<const char*>(&sMin), sizeof(float));
		fout.write(reinterpret_cast<const char*>(&ds), sizeof(float));

		for (size_t i = 0, n = sprites.size(); i < n; ++i)
		{
			wxgui::ISprite* sprite = sprites[i];

			int id = -1;
			for (size_t j = 0, m = m_merged.m_data.size(); j < m; ++j)
			{
				if (m_merged.m_data[j].filepath == sprite->getSymbol().getFilepath())
				{
					id = j;
					break;
				}
			}
			assert(id != -1);
			if (id >= 256)
				throw std::exception("PackageFileIOUtils::storeDataCompress id over 256");
			fout.write(reinterpret_cast<const char*>(&id), sizeof(byte));

			const f2Vec2& pos = sprite->getPosition();
			const int x = (dx == 0 ? 0 : (int)((pos.x - xMin) / dx + 0.5f));
			assert(x >= 0 && x <= 255);
			fout.write(reinterpret_cast<const char*>(&x), sizeof(byte));
			const int y = (dy == 0 ? 0 : (int)((pos.y - yMin) / dy + 0.5f));
			assert(y >= 0 && y <= 255);
			fout.write(reinterpret_cast<const char*>(&y), sizeof(byte));

			int angle = compressAngle(sprite->getAngle());
			assert(angle >= 0 && angle <= 255);
			fout.write(reinterpret_cast<const char*>(&angle), sizeof(byte));

			unsigned int type = compressType(sprite);
			fout.write(reinterpret_cast<const char*>(&type), sizeof(byte));

			if (sprite->getScale() != 1)
			{
				const int scale = (ds == 0 ? 0 : (int)((sprite->getScale() - sMin) / ds + 0.5f));
				assert(scale >= 0 && scale <= 255);
				fout.write(reinterpret_cast<const char*>(&scale), sizeof(byte));
			}
		}
	}
}

int PackageFileIOUtils::compressAngle(float angle)
{
	if (angle < 0) 
		angle += std::ceil((-angle) / (2*PI)) * 2*PI;
	else
		angle -= std::floor(angle / (2*PI)) * 2*PI;
	return (int)(angle / (2*PI) * 255 + 0.5f);
}

unsigned int PackageFileIOUtils::compressType(wxgui::ISprite* sprite)
{
	bool xMirror, yMirror;
	sprite->getMirror(xMirror, yMirror);
	unsigned int type = 0;
	if (xMirror) 
		type |= SPRITE_X_MIRROR;
	if (yMirror) 
		type |= SPRITE_Y_MIRROR;
	if (sprite->getScale() == 1)
		type |= NO_SCALE;
	return type;
}

void PackageFileIOUtils::loadHeader(std::ifstream& fin)
{
	fin.read(reinterpret_cast<char*>(&m_leftmost), sizeof(float));
	fin.read(reinterpret_cast<char*>(&m_gridWidth), sizeof(float));
}

void PackageFileIOUtils::loadData(std::ifstream& fin, Grids& internal, Grids& intersect)
{
	size_t gridSize;
	fin.read(reinterpret_cast<char*>(&gridSize), sizeof(size_t));
	internal.clear();
	internal.reserve(gridSize);
	for (size_t i = 0; i < gridSize; ++i)
	{
		std::vector<wxgui::ISprite*> sprites;
		loadData(fin, sprites);
		internal.push_back(sprites);
	}

	if (gridSize > 1)
	{
		intersect.clear();
		intersect.reserve(gridSize - 1);
		for (size_t i = 0, n = gridSize - 1; i < n; ++i)
		{
			std::vector<wxgui::ISprite*> sprites;
			loadData(fin, sprites);
			intersect.push_back(sprites);
		}
	}
}

void PackageFileIOUtils::loadData(std::ifstream& fin, std::vector<Grids>& internals, 
								  std::vector<Grids>& intersects)
{
	size_t size;
	fin.read(reinterpret_cast<char*>(&size), sizeof(size_t));
	internals.reserve(size);
	intersects.reserve(size);
	for (size_t i = 0; i < size; ++i)
	{
		Grids internal, intersect;
		loadData(fin, internal, intersect); 
		internals.push_back(internal);
		intersects.push_back(intersect);
	}
}

void PackageFileIOUtils::loadData(std::ifstream& fin, std::vector<wxgui::ISprite*>& sprites)
{
	size_t size;
	fin.read(reinterpret_cast<char*>(&size), sizeof(size_t));
	for (size_t i = 0; i < size; ++i)
	{
		int id;
		fin.read(reinterpret_cast<char*>(&id), sizeof(int));

		f2Vec2 pos;
		fin.read(reinterpret_cast<char*>(&pos.x), sizeof(float));
		fin.read(reinterpret_cast<char*>(&pos.y), sizeof(float));

		wxgui::ISymbol* symbol = wxgui::SymbolMgr::Instance()->getSymbol(m_merged.m_data[id].filepath);
		wxgui::ISprite* sprite = wxgui::SpriteFactory::create(symbol);

		float angle;
		fin.read(reinterpret_cast<char*>(&angle), sizeof(float));

		float scale;
		fin.read(reinterpret_cast<char*>(&scale), sizeof(float));

		unsigned int type;
		fin.read(reinterpret_cast<char*>(&type), sizeof(unsigned int));
		const bool xMirror = type & SPRITE_X_MIRROR,
			yMirror = type & SPRITE_Y_MIRROR;

		sprite->setTransform(pos, angle);
		sprite->setScale(scale);
		sprite->setMirror(xMirror, yMirror);

		sprites.push_back(sprite);
	}
}

void PackageFileIOUtils::addToStagePanel(const Grids& internal, const Grids& intersect)
{
	for (size_t i = 0, n = internal.size(); i < n; ++i)
	{
		for (size_t j = 0, m = internal[i].size(); j < m; ++j)
			m_spritesImpl->insertSprite(internal[i][j]);
	}
	for (size_t i = 0, n = intersect.size(); i < n; ++i)
	{
		for (size_t j = 0, m = intersect[i].size(); j < m; ++j)
			m_spritesImpl->insertSprite(intersect[i][j]);
	}
}