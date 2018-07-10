#ifndef _F2D_BV_FACTORY_H_
#define _F2D_BV_FACTORY_H_
#include "BVTypes.h"

namespace F2D
{
	class AbstractBV;

	class BVFactory
	{
	public:
		static AbstractBV* createBV(BV_TYPE type);

	}; // BVFactory
}

#endif // _F2D_BV_FACTORY_H_