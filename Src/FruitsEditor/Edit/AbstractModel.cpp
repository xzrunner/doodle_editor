#include "AbstractModel.h"
#include "../Dataset/LayersMgr.h"

using namespace FEDITOR;

AbstractModel::AbstractModel()
{
	m_layers = new LayersMgr;
}

AbstractModel::~AbstractModel()
{
	if (m_layers) delete m_layers;
}