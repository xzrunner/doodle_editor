#include "EditTrackChainCB.h"
#include "TrackChains.h"

using namespace FEDITOR;
using namespace FEDITOR::MOTOX::LEVEL;

EditTrackChainCB::EditTrackChainCB(TrackChains& trackChains)
	: m_trackChains(trackChains)
{
	m_trackChains.setCtlposDrawable(true);
}

EditTrackChainCB::~EditTrackChainCB()
{
	m_trackChains.setCtlposDrawable(false);
}

void EditTrackChainCB::afterKeyboard(unsigned char key)
{
	m_trackChains.createPhysFromAllChains();
}

void EditTrackChainCB::afterMouseLeftUp(const f2Vec2& pos)
{
	m_trackChains.createPhysFromAllChains();
}

void EditTrackChainCB::afterMouseRightUp(const f2Vec2& pos)
{
	m_trackChains.createPhysFromAllChains();
}