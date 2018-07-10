#include "ShapeFactory.h"
#include "PointShape.h"
#include "ChainShape.h"
#include "TriangleShape.h"

using namespace FEDITOR;

Shape* ShapeFactory::createShape(std::ifstream& fin)
{
	Shape* shape = NULL;

	std::string skip;
	int type;
	fin >> skip >> type;
	switch (type)
	{
	case e_point:
		shape = new PointShape();
		break;
	case e_chain:
		shape = new ChainShape();
		break;
	case e_triangle:
		shape = new TriangleShape();
		break;
	default:
		throw new IllegalArgumentException("ShapeFactory::createShape: error type. ");
	}
	shape->loadFromTextFile(fin);

	return shape;
}