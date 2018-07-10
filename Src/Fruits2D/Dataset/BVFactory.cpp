#include "BVFactory.h"
#include "AABB.h"
#include "OBB.h"

using namespace F2D;

AbstractBV* BVFactory::createBV(BV_TYPE type)
{
	AbstractBV* bv = NULL;
	switch (type)
	{
	case e_aabb:
		bv = new AABB;
		break;
	case e_obb:
		bv = new OBB;
		break;
	}
	return bv;
}