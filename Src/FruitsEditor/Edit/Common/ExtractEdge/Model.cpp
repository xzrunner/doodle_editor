#include "Model.h"
#include "Blackboard.h"
#include "SameColorRegionSelect.h"
#include "Dataset/Layer.h"
#include "Dataset/Sprite.h"
#include "Dataset/ChainShape.h"
#include "Dataset/Texture.h"
#include "Dataset/LayersMgr.h"
#include "Dataset/ShapeFactory.h"
#include "File/FileNameParser.h"
#include "File/ImgFileAdapter.h"
#include "File/LoopsFileAdapter.h"

using namespace FEDITOR;
using namespace FEDITOR::EXTRACT_EDGE;

Model::Model(const AbstractBlackboard* blackboard)
{
	m_blackboard = static_cast<Blackboard*>(const_cast<AbstractBlackboard*>(blackboard));
	initLayers();
}

Model::~Model()
{
	if (m_autoSelect) delete m_autoSelect;
}

void Model::handleEvent(const Event& event)
{
	switch (event.getID())
	{
	case Blackboard::e_OpenFile:
		loadFromFile(event.getInfo());
		break;

	case Blackboard::e_SetCoordLinesVisible:
		setCoordLinesLayerVisible();
		break;
	case Blackboard::e_ChangeCoordLines:
		buildCoordLinesSprite();
		setCoordLinesPosition();
		break;

	case Blackboard::e_SavePolyline:
		storeToTextFile();
		break;

	case Blackboard::e_SetColorTol:
		if (m_autoSelect)
		{
			m_autoSelect->selectByPos();
			refreshAutoSelectLayer();
		}
		break;
	case Blackboard::e_SetEdgeTol:
		if (m_autoSelect) 
		{
			m_autoSelect->simplifyBoundaries();
			refreshAutoSelectLayer();
		}
		break;
	case Blackboard::e_AutoSelect:
		if (!m_autoSelect) 
			m_autoSelect = new SameColorRegionSelect(m_blackboard, *m_bgTexture);
		break;
	}
}

void Model::refreshAutoSelectLayer()
{
	m_autoLayer->clearSprites();
	m_autoSelect->addDataToLayer(m_autoLayer);
}

f2Vec2 Model::getCoordsInCurrentType(const f2Vec2& pos) const
{
	switch (m_blackboard->m_coordsType)
	{
	case 0:
		return pos;
	case 1:
		{
			const float x = pos.x + m_bgTexture->getWidth() * 0.5f,
				y = pos.y + m_bgTexture->getHeight() * 0.5f;
			return f2Vec2(x, y);
		}
	case 2:
		{
			const float x = pos.x + m_bgTexture->getWidth() * 0.5f,
				y = m_bgTexture->getHeight() - (pos.y + m_bgTexture->getHeight() * 0.5f);
			return f2Vec2(x, y);
		}
	default:
		return pos;
	}
}

void Model::initLayers()
{
	Layer* bgLayer = new Layer(Layer::e_lowermost);
	m_bgSprite = new Sprite;
	bgLayer->addSprite(m_bgSprite);
	m_dataLayer = new Layer(Layer::e_middle);
	m_edgeSprite = new Sprite;
	m_dataLayer->addSprite(m_edgeSprite);
	m_autoLayer = new Layer(Layer::e_middle);
	m_coordLinesLayer = new Layer(Layer::e_middle);
	Layer* tmpLayer = new Layer(Layer::e_uppermost);
	setCoordLinesLayerVisible();

	m_layers->addLayer(bgLayer);
	m_layers->addLayer(m_dataLayer);
	m_layers->addLayer(m_autoLayer);
	m_layers->addLayer(m_coordLinesLayer);
	m_layers->addLayer(tmpLayer);

	m_bgTexture = NULL;

	m_autoSelect = NULL;

	m_coordLinesSprite = NULL;
}

void Model::loadFromFile(const std::string& filename)
{
	FileNameParser::Type type = FileNameParser::getFileType(filename);
	switch (type)
	{
	case FileNameParser::e_img:
		loadBgLayer(filename);
		break;
	case FileNameParser::e_loops:
		loadFromLoopsFile(filename);
		handleEvent(Event(Blackboard::e_ChangeCoordLines));
		break;
	}
}

void Model::loadFromLoopsFile(const std::string& filename)
{
	LoopsFileAdapter fa;
	fa.load(filename);

	loadBgLayer(fa.m_imgFilename);

	Blackboard* bb = const_cast<Blackboard*>(m_blackboard);
	bb->m_coordsType = fa.m_coordsType;

	m_edgeSprite->clearShapes();
	for (size_t i = 0, n = fa.m_loops.size(); i < n; ++i)
	{
		ChainShape* loop = fa.m_loops[i]->clone();
		restoreShapeCoords(loop);
		m_edgeSprite->pushShape(loop);
	}
}

void Model::storeToTextFile() const
{
	if (!m_bgTexture->isValid())
		return;

	const std::string filename = 
		m_bgTexture->getFilename(true) + 
		FileNameParser::getFileExtension(FileNameParser::e_loops) + 
		".txt";
	std::ofstream fout(filename.c_str());

	fout << m_bgTexture->getFilename(false) << '\n';

	fout << m_blackboard->m_coordsType << '\n';

	const std::vector<Shape*>& shapes = m_edgeSprite->getAllShapes();
	fout << shapes.size() << '\n';
	for (size_t i = 0, n = shapes.size(); i < n; ++i)
	{
		ChainShape* shape = dynamic_cast<ChainShape*>(shapes[i]);
		assert(shape && shape->m_isLoop);
		adjustShapeCoords(shape);
		shape->storeToTextFile(fout);
		restoreShapeCoords(shape);
	}

	fout.close();
}

void Model::loadBgLayer(const std::string& file)
{
	if (FileNameParser::isType(file, FileNameParser::e_img))
	{
		ImgFileAdapter fa;
		fa.m_sprite = m_bgSprite;
		fa.load(file);

		m_bgTexture = TexturesMgr::Instance()->getItem(file);
		buildCoordLinesLayer();
	}
}

void Model::buildCoordLinesLayer()
{
	if (!m_bgTexture) return;

	m_coordLinesLayer->clearSprites();
	m_coordLinesLayer->m_style.m_bDrawCtlPos = false;
	m_coordLinesLayer->m_style.m_chainStyle.size = 6;
	m_coordLinesLayer->m_style.m_chainStyle.color = f2Colorf(0, 0, 0);

	m_coordLinesSprite = new Sprite;
	buildCoordLinesSprite();

	m_coordLinesLayer->addSprite(m_coordLinesSprite);
}

void Model::buildCoordLinesSprite()
{
	if (!m_bgTexture) return;

	const float w = m_bgTexture->getWidth(),
		h = m_bgTexture->getHeight();

	m_coordLinesSprite->clearShapes();
	switch (m_blackboard->m_coordsType)
	{
	case 0:
		{
			ChainShape* line = new ChainShape;
			line->pushBack(f2Vec2(- w * 0.5f * 1.1f, 0.0f));
			line->pushBack(f2Vec2(  w * 0.5f * 1.1f, 0.0f));
			m_coordLinesSprite->pushShape(line);
			line = new ChainShape;
			line->pushBack(f2Vec2(0.0f, - h * 0.5f * 1.1f));
			line->pushBack(f2Vec2(0.0f,   h * 0.5f * 1.1f));
			m_coordLinesSprite->pushShape(line);
		}
		break;
	case 1:
		{
			ChainShape* line = new ChainShape;
			line->pushBack(f2Vec2(- w * 0.1f, 0.0f));
			line->pushBack(f2Vec2(  w * 1.1f, 0.0f));
			m_coordLinesSprite->pushShape(line);
			line = new ChainShape;
			line->pushBack(f2Vec2(0.0f, - h * 0.1f));
			line->pushBack(f2Vec2(0.0f,   h * 1.1f));
			m_coordLinesSprite->pushShape(line);
		}
		break;
	case 2:
		{
			ChainShape* line = new ChainShape;
			line->pushBack(f2Vec2(- w * 0.1f, 0.0f));
			line->pushBack(f2Vec2(  w * 1.1f, 0.0f));
			m_coordLinesSprite->pushShape(line);
			line = new ChainShape;
			line->pushBack(f2Vec2(0.0f, - h * 1.1f));
			line->pushBack(f2Vec2(0.0f,   h * 0.1f));
			m_coordLinesSprite->pushShape(line);
		}
		break;
	}
}

void Model::setCoordLinesPosition()
{
	f2Vec2 pos;
	switch (m_blackboard->m_coordsType)
	{
	case 0:
		pos.x = pos.y = 0;
		break;
	case 1:
		pos.x = - m_bgTexture->getWidth() * 0.5f;
		pos.y = - m_bgTexture->getHeight() * 0.5f;
		break;
	case 2:
		pos.x = - m_bgTexture->getWidth() * 0.5f;
		pos.y =   m_bgTexture->getHeight() * 0.5f;
		break;
	}

	m_coordLinesSprite->setTransform(pos, 0);
}

void Model::setCoordLinesLayerVisible()
{
	m_coordLinesLayer->setVisible(m_blackboard->m_drawCoordLines == 1);
}

void Model::adjustShapeCoords(ChainShape* shape) const
{
	switch (m_blackboard->m_coordsType)
	{
	case 0:
		break;
	case 1:
		for (size_t i = 0, n = shape->m_vertices.size(); i < n; ++i)
		{
			shape->m_vertices[i].x += m_bgTexture->getWidth() * 0.5f;
			shape->m_vertices[i].y += m_bgTexture->getHeight() * 0.5f;
		}
		break;
	case 2:
		for (size_t i = 0, n = shape->m_vertices.size(); i < n; ++i)
		{
			shape->m_vertices[i].x += m_bgTexture->getWidth() * 0.5f;
			shape->m_vertices[i].y = m_bgTexture->getHeight() - (shape->m_vertices[i].y + m_bgTexture->getHeight() * 0.5f);
		}
		break;
	}
}

void Model::restoreShapeCoords(ChainShape* shape) const
{
	switch (m_blackboard->m_coordsType)
	{
	case 0:
		break;
	case 1:
		for (size_t i = 0, n = shape->m_vertices.size(); i < n; ++i)
		{
			shape->m_vertices[i].x -= m_bgTexture->getWidth() * 0.5f;
			shape->m_vertices[i].y -= m_bgTexture->getHeight() * 0.5f;
		}
		break;
	case 2:
		for (size_t i = 0, n = shape->m_vertices.size(); i < n; ++i)
		{
			shape->m_vertices[i].x -= m_bgTexture->getWidth() * 0.5f;
			shape->m_vertices[i].y = m_bgTexture->getHeight() - shape->m_vertices[i].y - m_bgTexture->getHeight() * 0.5f;
		}
		break;
	}
}