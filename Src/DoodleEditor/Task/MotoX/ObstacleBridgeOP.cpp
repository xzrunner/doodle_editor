#include "ObstacleBridgeOP.h"
#include "ObstacleBridgeCMPT.h"
#include "StagePanel.h"
#include "TrackChain.h"
#include "ObstacleBridgeData.h"

using namespace deditor::motox;

ObstacleBridgeOP::ObstacleBridgeOP(StagePanel* stagePanel, ObstacleBridgeCMPT* cmpt)
	: ZoomViewOP(stagePanel, true)
	, m_stagePanel(stagePanel)
	, m_cmpt(cmpt)
	, m_selected(NULL)
{
	m_beginPos.setInvalid();
	m_endPos.setInvalid();
}

ObstacleBridgeOP::~ObstacleBridgeOP()
{
	clear();
}

bool ObstacleBridgeOP::onMouseLeftDown(int x, int y)
{
	if (ZoomViewOP::onMouseLeftDown(x, y)) return true;

	f2Vec2 pos = m_editPanel->transPosScreenToProject(x, y);
	queryByPos(pos);

	if (!m_selected)
	{
		if (!m_beginPos.isValid())
		{
			m_beginPos = m_editPanel->transPosScreenToProject(x, y);
		}
		else if (!m_endPos.isValid())
		{
			m_endPos = m_editPanel->transPosScreenToProject(x, y);
			createBridge();
			m_editPanel->Refresh();
		}
		else
		{
			m_beginPos = m_editPanel->transPosScreenToProject(x, y);
			m_endPos.setInvalid();
		}
	}

	return false;
}

bool ObstacleBridgeOP::onMouseLeftUp(int x, int y)
{
	if (ZoomViewOP::onMouseLeftUp(x, y)) return true;

	if (m_selected)
	{
		if (m_bSelectStart) m_selected->start = m_editPanel->transPosScreenToProject(x, y);
		else m_selected->end = m_editPanel->transPosScreenToProject(x, y);
		m_selected->bridgeMesh->build(m_selected->start, m_selected->end);

		m_editPanel->Refresh();
	}

	return false;
}

bool ObstacleBridgeOP::onMouseDrag(int x, int y)
{
	if (ZoomViewOP::onMouseDrag(x, y)) return true;

	if (m_selected)
	{
		if (m_bSelectStart) m_selected->start = m_editPanel->transPosScreenToProject(x, y);
		else m_selected->end = m_editPanel->transPosScreenToProject(x, y);
		m_selected->bridgeMesh->build(m_selected->start, m_selected->end);

		m_editPanel->Refresh();
	}

	return false;
}

bool ObstacleBridgeOP::onDraw() const
{
	if (wxgui::ZoomViewOP::onDraw()) return true;

	for (size_t i = 0, n = m_bridges.size(); i < n; ++i)
	{
		Bridge* bridge = m_bridges[i];
		wxgui::PrimitiveDraw::drawCircle(bridge->start, END_POS_RADIUS, f2Colorf(0.8f, 0.2f, 0.2f));
		wxgui::PrimitiveDraw::drawCircle(bridge->end, END_POS_RADIUS, f2Colorf(0.8f, 0.2f, 0.2f));
	}

	return false;
}

bool ObstacleBridgeOP::clear()
{
	if (wxgui::ZoomViewOP::clear()) return true;

	m_beginPos.setInvalid();
	m_endPos.setInvalid();

	for_each(m_bridges.begin(), m_bridges.end(), DeletePointerFunctor<Bridge>());
	m_bridges.clear();

	m_selected = NULL;

	return false;
}

void ObstacleBridgeOP::createBridge()
{
	const std::vector<TrackChain*>& chains = m_stagePanel->getTrackChains();
	BridgeData* bridgeMesh = new BridgeData(m_stagePanel->getWorld(), chains[0]->getBody(), m_cmpt->getTileSymbol());

	bridgeMesh->build(m_beginPos, m_endPos);

	Bridge* bridge = new Bridge;
	bridge->bridgeMesh = bridgeMesh;
	bridge->start = m_beginPos;
	bridge->end = m_endPos;
	m_bridges.push_back(bridge);

	wxgui::ISprite* sprite = wxgui::SpriteFactory::create(m_cmpt->getTileSymbol());
	sprite->setUserData(bridgeMesh);
	m_stagePanel->insertSprite(sprite);
}

void ObstacleBridgeOP::queryByPos(const f2Vec2& pos)
{
	m_selected = NULL;
	for (size_t i = 0, n = m_bridges.size(); i < n; ++i)
	{
		Bridge* bridge = m_bridges[i];
		if (f2Math::getDistance(pos, bridge->start) < END_POS_RADIUS)
		{
			m_selected = bridge;
			m_bSelectStart = true;
			break;
		}
		else if (f2Math::getDistance(pos, bridge->end) < END_POS_RADIUS)
		{
			m_selected = bridge;
			m_bSelectStart = false;
			break;
		}
	}
}