#include "Model.h"
#include "Blackboard.h"

using namespace FEDITOR;
using namespace FEDITOR::SOFT_RENDER;

Model::Model(const AbstractBlackboard* blackboard)
{
	m_blackboard = static_cast<Blackboard*>(const_cast<AbstractBlackboard*>(blackboard));
	initLayers();
}

Model::~Model()
{
}

void Model::handleEvent(const Event& event)
{
	switch (event.getID())
	{
	}
}

void Model::initLayers()
{
}