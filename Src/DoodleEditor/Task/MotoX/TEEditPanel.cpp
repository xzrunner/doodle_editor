#include "TEEditPanel.h"
#include "TECanvas.h"
#include "LibraryTemplateItem.h"

using namespace deditor::motox;

TEEditPanel::TEEditPanel(wxWindow* parent, wxgui::LibraryPanel* libraryPanel,
						 LibraryTemplateItem* templateItem)
	: EditPanel(parent)
	, wxgui::SpritesPanelImpl(this, libraryPanel)
	, m_libraryPanel(libraryPanel)
	, m_templateItem(templateItem)
{
	m_editOP = NULL;
	m_canvas = new TECanvas(this);

	load();
}

TEEditPanel::~TEEditPanel()
{
	store();
	m_templateItem->computeCenter();
}

void TEEditPanel::setItemName(const wxString& filename)
{
	m_templateItem->setName(filename);
}

void TEEditPanel::load()
{
	SpritesPanelImpl::clear();
	for (size_t i = 0, n = m_templateItem->m_sprites.size(); i < n; ++i)
		insertSprite(m_templateItem->m_sprites[i]);
}

void TEEditPanel::store()
{
	for (size_t i = 0, n = m_templateItem->m_sprites.size(); i < n; ++i)
		m_templateItem->m_sprites[i]->release();
	m_templateItem->m_sprites.clear();

	traverseSprites(FetchAllVisitor<wxgui::ISprite>(m_templateItem->m_sprites));
	float cx = 0;
	for (size_t i = 0, n = m_templateItem->m_sprites.size(); i < n; ++i)
	{
		cx += m_templateItem->m_sprites[i]->getPosition().x;
		m_templateItem->m_sprites[i]->retain();
	}
	cx /= m_templateItem->m_sprites.size();
	for (size_t i = 0, n = m_templateItem->m_sprites.size(); i < n; ++i)
		m_templateItem->m_sprites[i]->translate(f2Vec2(-cx, 0.0f));
}