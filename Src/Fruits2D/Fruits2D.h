#ifndef _F2D_H_
#define _F2D_H_

#include "Tools/Tools.h"
#include "Tools/f2Types.h"
#include "Tools/f2Math.h"
#include "Tools/Random.h"
#include "Tools/visitors.h"
#include "Tools/UserDataImpl.h"

#include "Dataset/Object.h"
#include "Dataset/f2Sprite.h"
#include "Dataset/f2Shape.h"
#include "Dataset/AbstractBV.h"
#include "Dataset/BVFactory.h"
#include "Dataset/AABB.h"
#include "Dataset/OBB.h"

#include "Algorithms/DelaunayTriangulation.h"
#include "Algorithms/DouglasPeucker.h"
#include "Algorithms/CosineSmooth.h"
#include "Algorithms/SGI.h"

using namespace F2D;

#endif // _F2D_H_