#include "Sprite.h"
#include "TextureRegion.h"
#include "ChainShape.h"
#include "ShapeFactory.h"
#include "BodyFactory.h"
#include "../File/FileNameParser.h"
#include "../File/ImgFileAdapter.h"
#include "../File/ChainsFileAdapter.h"
#include "../File/CircleFileAdapter.h"
#include <Box2D/Box2D.h>

using namespace FEDITOR;

Sprite::Sprite(float scale/* = 1.0f*/, BV_TYPE bvType/* = e_obb*/)
{
	m_position.x = m_position.y = 0;
	m_angle = 0;
	m_xScale = m_yScale = scale;

	m_body = NULL;

	m_bounding = BVFactory::createBV(bvType);

	m_texture = NULL;

	m_userData = NULL;
}

Sprite::Sprite(const Sprite& sprite)
{
	m_position = sprite.getPosition();
	m_angle = sprite.getAngle();
	m_xScale = sprite.m_xScale;
	m_yScale = sprite.m_yScale;

	m_bounding = dynamic_cast<AbstractBV*>(const_cast<Sprite*>(&sprite)->getBounding()->clone());

	const std::vector<TextureRegion*>& textures = sprite.getAllTextureRegions();
	for (size_t i = 0, n = textures.size(); i < n; ++i)
		pushTextureRegion(textures[i]->clone(), false);

	const std::vector<Shape*>& shapes = sprite.getAllShapes();
	for (size_t i = 0, n = shapes.size(); i < n; ++i)
		pushShape(dynamic_cast<Shape*>(shapes[i]->clone()), false);

	Body* body = sprite.getBody();
	if (body) m_body = body->clone();
	else m_body = NULL;
}

Sprite::~Sprite()
{
	clearTextureRegions();
	clearShapes();
	delete m_body;
	delete m_userData;
}

Sprite* Sprite::clone()
{
	return new Sprite(*this);
}

void Sprite::loadFromTextFile(std::ifstream& fin)
{
	size_t size;
	// texture
	clearTextureRegions();
	fin >> size;
	m_textureRegions.reserve(size);
	for (size_t i = 0; i < size; ++i)
	{
		TextureRegion* region = new TextureRegion;
		region->loadFromTextFile(fin);
		m_textureRegions.push(region);
	}
	// shape
	clearShapes();
	fin >> size;
	m_shapes.reserve(size);
	for (size_t i = 0; i < size; ++i)
	{
		Shape* shape = ShapeFactory::createShape(fin);
		m_shapes.push(shape);
	}
	// params
	fin >> m_position >> m_angle >> m_xScale >> m_yScale;
	// BV
	m_bounding->loadFromTextFile(fin);
}

void Sprite::storeToTextFile(std::ofstream& fout) const
{
	m_textureRegions.storeToTextFile(fout);
	m_shapes.storeToTextFile(fout);

	fout << m_position << '\n' << m_angle << " " << m_xScale << " " << m_yScale << '\n';
	
	m_bounding->storeToTextFile(fout);
}

void Sprite::loadFromUnknownFile(const std::string& filename)
{
	m_filename = filename;
	FileNameParser::Type type = FileNameParser::getFileType(filename);
	switch (type)
	{
	case FileNameParser::e_img:
		loadFromImgFile(filename);
		break;
	case FileNameParser::e_loops:
		loadFromLoopsFile(filename);
		break;
	case FileNameParser::e_chains:
		loadFromChainsFile(filename);
		break;
	case FileNameParser::e_circle:
		loadFromCircleFile(filename);
		break;
	default:
		m_filename = "";
	}
}

const std::string& Sprite::getFilename() const
{
	return m_filename;
}

void Sprite::pushTextureRegion(TextureRegion* textureRegion, bool refreshBounding/* = true*/) 
{ 
	m_textureRegions.push(textureRegion);
	if (refreshBounding)
	{
		f2AABB r;
		textureRegion->getAABB(r, m_position, m_angle);
		r *= getScale();
		m_bounding->combine(r);
	}
}

void Sprite::clearTextureRegions() 
{ 
	m_textureRegions.clear(); 
	rebuildBounding();
}

void Sprite::pushShape(Shape* shape, bool refreshBounding/* = true*/) 
{ 
	m_shapes.push(shape);
	if (refreshBounding)
	{
		f2AABB r;
		shape->getAABB(r, m_position, m_angle);
		r *= getScale();
		m_bounding->combine(r);
	}
}

Shape* Sprite::popShape()
{
	Shape* shape = m_shapes.pop();
	rebuildBounding();
	return shape;
}

void Sprite::clearShapes() 
{ 
	m_shapes.clear(); 
	rebuildBounding();
}

f2Vec2 Sprite::transToLocalPosition(const f2Vec2& pos) const
{
	return f2Math::rotateVector(pos - m_position, -m_angle) + m_position;
}

void Sprite::translate(const f2Vec2& offset)
{
	m_bounding->translate(offset);
	m_position += offset;
}

void Sprite::rotate(float delta)
{
	m_bounding->rotate(delta);
	if (!m_bounding->isValid()) rebuildBounding();
	m_angle += delta;
}

void Sprite::setTransform(const f2Vec2& position, float angle)
{
	translate(position - m_position);
	if (angle != m_angle) rotate(angle - m_angle);

	if (m_body)
	{
		m_body->getBody()->SetTransform(b2Vec2(position.x, position.y), angle);
	}
}

void Sprite::setScale(float xScale, float yScale, bool updatePhysAndAABB/* = false*/)
{
	m_xScale = xScale;
	m_yScale = yScale;
	if (updatePhysAndAABB)
	{
		rebuildBounding();
		if (m_body)
		{
			delete m_body;
			m_body = BodyFactory::createBody(m_filename, getScale());
			m_body->setTransform(getPosition(), getAngle());
			m_body->setAlive(true);
		}
	}
}

void Sprite::rebuildBounding()
{
	f2AABB bounding;
	{
		f2AABB r;
		m_textureRegions.getAABB(r, m_position, m_angle);
		bounding.combine(r);
	}
	{
		f2AABB r;
		m_shapes.getAABB(r, m_position, m_angle);
		bounding.combine(r);
	}
	bounding *= getScale();

	// m_body ...

	m_bounding->initFromAABB(bounding);
}

void Sprite::updateEachFrame()
{
	if (!m_body) return;
	b2Body* body = m_body->getBody();
	if (!body) return;

	if (m_body->isAlive())
	{
		const b2Vec2& pos = body->GetPosition();
		setTransform(f2Vec2(pos.x, pos.y), body->GetAngle());
	}
	else
	{
		body->SetTransform(b2Vec2(m_position.x, m_position.y), m_angle);
	}
}

bool Sprite::isContain(const f2Vec2& pos, bool isAccurate/* = false*/) const
{
	if (isAccurate)
	{
		const f2Vec2 transform = transToLocalPosition(pos);

		const std::vector<TextureRegion*>& regions = m_textureRegions.getAll();
		for (size_t i = 0, n = regions.size(); i < n; ++i)
			if (regions[i]->isContain(transform)) return true;

		const std::vector<Shape*>& shapes = m_shapes.getAll();
		for (size_t i = 0, n = shapes.size(); i < n; ++i)
			if (shapes[i]->isContain(transform, getScale())) return true;

		return false;
	}
	else
	{
		return m_bounding->isContain(pos); 
	}
}

bool Sprite::isIntersect(const f2AABB& aabb) const
{
	return m_bounding->isIntersect(aabb);
}

void Sprite::loadFromImgFile(const std::string& filename)
{
	ImgFileAdapter fa;
	fa.m_sprite = this;
	fa.load(filename);
}

void Sprite::loadFromLoopsFile(const std::string& filename)
{
	std::string texName;
	std::ifstream fin(filename.c_str());
	fin >> texName;
	fin.close();
	loadFromImgFile(texName);

	if (m_body) delete m_body;
	m_body = BodyFactory::createBody(filename, getScale());
}

void Sprite::loadFromChainsFile(const std::string& filename)
{
	ChainsFileAdapter fa;
	fa.load(filename);

	clearShapes();
	for (size_t i = 0, n = fa.m_chains.size(); i < n; ++i)
		pushShape(fa.m_chains[i]->clone());
}

void Sprite::loadFromCircleFile(const std::string& filename)
{
	CircleFileAdapter fa;
	fa.load(filename);

	loadFromImgFile(fa.m_imgFilename);

	if (m_body) delete m_body;
	m_body = BodyFactory::createBody(filename, getScale());
}