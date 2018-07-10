#include "StagePanel.h"
#include "ArrangeSpriteOP.h"
#include "StageCanvas.h"
//#include "BinaryTreeArrange.h"
#include "RectBinArrange.h"

using namespace deditor::automatic_merge;

StagePanel::StagePanel(wxWindow* parent, wxgui::PropertySettingPanel* propertyPanel,
					   wxgui::LibraryPanel* libraryPanel)
	: EditPanel(parent)
	, SpritesPanelImpl(this, libraryPanel)
{
	m_editOP = new ArrangeSpriteOP(this, propertyPanel);
	m_canvas = new StageCanvas(this);
//	m_strategy = new BinaryTreeArrange();
	m_strategy = new RectBinArrange();
}

void StagePanel::removeSprite(wxgui::ISprite* sprite)
{
	wxgui::SpritesPanelImpl::removeSprite(sprite);
	arrangeAllSprites(false);
}

void StagePanel::insertSprite(wxgui::ISprite* sprite)
{
	wxgui::SpritesPanelImpl::insertSprite(sprite);
	arrangeAllSprites(false);
}

void StagePanel::clear()
{
	EditPanel::clear();
	SpritesPanelImpl::clear();
}

void StagePanel::setOutputImageSize(int width, int height)
{
	m_width = width;
	m_height = height;
	((StageCanvas*)m_canvas)->setOutputImageSize(width, height);
	arrangeAllSprites(true);
}

void StagePanel::arrangeAllSprites(bool bClearSelection)
{
	if (bClearSelection) m_spriteSelection->clear();

	std::vector<wxgui::ImageSprite*> sprites;
	traverseSprites(FetchAllVisitor<wxgui::ImageSprite>(sprites), wxgui::e_editable);
	m_strategy->arrange(sprites, m_width, m_height);
}

void StagePanel::loadLibraryList()
{
	clear();

	wxgui::ISymbol* symbol = NULL;
	int index = 0;
	while (true)
	{
		symbol = m_libraryPanel->getSymbol(index++);
		if (!symbol) 
			break;
		else 
		{
			wxgui::ISprite* sprite = wxgui::SpriteFactory::create(symbol);
			wxgui::SpritesPanelImpl::insertSprite(sprite);
		}
	}

	arrangeAllSprites(true);
}