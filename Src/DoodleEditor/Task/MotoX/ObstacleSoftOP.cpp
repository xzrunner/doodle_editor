#include "ObstacleSoftOP.h"
#include "ObstacleSoftCMPT.h"
#include "ObstacleSoftData.h"
#include "StagePanel.h"

using namespace deditor::motox;

ObstacleSoftOP::ObstacleSoftOP(StagePanel* stagePanel, 
							   wxgui::LibraryPanel* libraryPanel, 
							   ObstacleSoftCMPT* cmpt)
	: ZoomViewOP(stagePanel, true)
	, m_stagePanel(stagePanel)
	, m_libraryPanel(libraryPanel)
	, m_cmpt(cmpt)
{
	m_pos.setInvalid();
}

bool ObstacleSoftOP::onMouseLeftDown(int x, int y)
{
	if (ZoomViewOP::onMouseLeftDown(x, y)) return true;

	wxgui::ImageSymbol* symbol = dynamic_cast<wxgui::ImageSymbol*>(m_libraryPanel->getSymbol());
	if (!symbol) return false;
	
	m_pos = m_editPanel->transPosScreenToProject(x, y);
	wxgui::ISprite* sprite = wxgui::SpriteFactory::create(symbol);
	sprite->translate(m_pos);

	ObstacleSoftCMPT::SoftSettings settings;
	m_cmpt->getSettings(settings);

	SoftData* mesh = NULL;
	if (settings.shape == ObstacleSoftCMPT::SoftSettings::e_poly)
		mesh = new SoftPolyData(m_stagePanel->getWorld());
	else if (settings.shape == ObstacleSoftCMPT::SoftSettings::e_circle)
		mesh = new SoftCircleData(m_stagePanel->getWorld());
	else
		assert(0);

	SoftDataDef def;
	def.width = symbol->getWidth();
	def.height = symbol->getHeight();
	def.edge = settings.edge;
	def.frequencyHz = settings.frequencyHz;
	def.dampingRatio = settings.dampingRatio;
	def.nodeHalfEdge = 0.5f / BOX2D_SCALE_FACTOR;

	mesh->build(def, m_pos);

	sprite->setUserData(mesh);
	m_stagePanel->insertSprite(sprite);

	return false;
}

bool ObstacleSoftOP::onMouseMove(int x, int y)
{
	if (ZoomViewOP::onMouseMove(x, y)) return true;

	m_pos = m_editPanel->transPosScreenToProject(x, y);
	m_editPanel->Refresh();

	return false;
}

bool ObstacleSoftOP::onDraw() const
{
	if (ZoomViewOP::onDraw()) return true;

	wxgui::ISymbol* symbol = m_libraryPanel->getSymbol();
	if (symbol && m_pos.isValid())
		wxgui::SpriteDraw::drawSprite(symbol, m_pos);

	return false;
}

bool ObstacleSoftOP::clear()
{
	if (ZoomViewOP::clear()) return true;

	m_pos.setInvalid();

	return false;
}