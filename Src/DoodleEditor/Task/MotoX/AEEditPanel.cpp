#include "AEEditPanel.h"
#include "AEPartsOP.h"
#include "Frame/defs.h"

using namespace deditor::motox;

AEEditPanel::AEEditPanel(wxWindow* parent, wxgui::LibraryPanel* libraryPanel,
						 LibraryActorItem& params)
	: EditPanel(parent)
	, MultiSpritesImpl(parent)
	, m_parts(params)
	, m_joints(m_world, params, m_parts)
	, m_params(params)
	, m_libraryPanel(libraryPanel)
{
	m_ground = NULL;
	initBackground();

	m_editOP = NULL;
	m_canvas = new AECanvas(this);
	SetDropTarget(new DragSymbolTarget(this));
}

AEEditPanel::~AEEditPanel()
{
	delete m_ground;
}

void AEEditPanel::traverseSprites(IVisitor& visitor, 
								  wxgui::TraverseType type/* = wxgui::e_allExisting*/,
								  bool order/* = true*/) const
{
	m_parts.traverse(visitor);
}

void AEEditPanel::clear()
{
	m_spriteSelection->clear();
	m_joints.clear();
	m_parts.clear();
}

void AEEditPanel::insertSprite(int index, wxCoord x, wxCoord y)
{
	AEPartsOP* partsOP = static_cast<AEPartsOP*>(m_editOP);
	if (partsOP)
	{
		wxgui::ISymbol* symbol = m_libraryPanel->getSymbol(index);
		if (symbol)
		{
			f2Vec2 pos = transPosScreenToProject(x, y);
			partsOP->loadPart(symbol, pos);
			Refresh();
		}
	}
}

void AEEditPanel::update(wxCommandEvent& event)
{
	wxgui::PhysicsPanelImpl::update(event);
	traverseSprites(UpdateVisitor());
	Refresh();
}

void AEEditPanel::loadDataFromFile(std::ifstream& fin)
{
	m_params.loadFromTextFile(fin);
	m_parts.initFromParams();
	m_joints.initFromParams();
}

void AEEditPanel::storeDataToFile(std::ofstream& fout) const
{
	m_params.storeToTextFile(fout);
}

void AEEditPanel::initBackground()
{
	std::vector<f2Vec2> vertices;
	vertices.push_back(f2Vec2(-SCREEN_WIDTH * 0.5f, -SCREEN_HEIGHT * 0.5f));
	vertices.push_back(f2Vec2( SCREEN_WIDTH * 0.5f, -SCREEN_HEIGHT * 0.5f));
	vertices.push_back(f2Vec2( SCREEN_WIDTH * 0.5f,  SCREEN_HEIGHT * 0.5f));
	vertices.push_back(f2Vec2(-SCREEN_WIDTH * 0.5f,  SCREEN_HEIGHT * 0.5f));

	m_ground = new wxgui::ChainBody(m_world, vertices, true);
}

//////////////////////////////////////////////////////////////////////////
// class AEEditPanel::DragSymbolTarget
//////////////////////////////////////////////////////////////////////////

AEEditPanel::DragSymbolTarget::
DragSymbolTarget(AEEditPanel* panelImpl)
{
	m_panelImpl = panelImpl;
}

bool AEEditPanel::DragSymbolTarget::
OnDropText(wxCoord x, wxCoord y, const wxString& data)
{
 	wxString sType = data.substr(0, data.find(","));
 	wxString sIndex = data.substr(data.find(",") + 1);
 
 	long index;
 	sIndex.ToLong(&index);
 
 	m_panelImpl->insertSprite(index, x, y);

	return true;
}

//////////////////////////////////////////////////////////////////////////
// class AEEditPanel::UpdateVisitor
//////////////////////////////////////////////////////////////////////////

void AEEditPanel::UpdateVisitor::
visit(IObject* object, bool& bFetchNext)
{
	wxgui::ISprite* sprite = static_cast<wxgui::ISprite*>(object);
	sprite->updateEachFrame();
	bFetchNext = true;
}