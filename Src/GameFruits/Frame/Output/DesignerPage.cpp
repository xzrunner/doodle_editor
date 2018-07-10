#include "DesignerPage.h"
#include "Dataset/DataConnection.h"
#include "Dataset/Object.h"
#include "Dataset/Scene.h"
#include "Dataset/InterimData.h"
#include "Frame/View/Backstage/DstPanel.h"
#include "Frame/View/Library/ScenePage.h"

using namespace GAME_FRUITS;
using namespace GAME_FRUITS::OUTPUT;

BEGIN_EVENT_TABLE(DesignerPage, wxWindow)
	EVT_SIZE(DesignerPage::onSize)
	EVT_MOUSE_EVENTS(DesignerPage::onMouse)
	EVT_KEY_DOWN(DesignerPage::onKey)
	EVT_PAINT(DesignerPage::onPaint)
END_EVENT_TABLE()

DesignerPage::DesignerPage(wxWindow* parent)
	: wxWindow(parent, wxID_ANY)
{
	SetDropTarget(new DragTileTarget(this));
}

void DesignerPage::storeToInterimData(InterimData& interim) const
{
	DataConnection::m_currScene->storeToInterimData(interim);
}

void DesignerPage::loadFromInterimData(const InterimData& interim)
{
	DataConnection::m_currScene->loadFromInterimData(interim);
}

void DesignerPage::addSprite(const wxString& path, int x, int y)
{
	DataConnection::m_currScene->addImage(path, x - m_origin.x, y - m_origin.y);

	VIEW::LIBRARY::ScenePage* page = dynamic_cast<VIEW::LIBRARY::ScenePage*>(DataConnection::m_libraryNotebook->GetPage(1));
	assert(page);
	page->updateThumbnail(*DataConnection::m_currScene);
}

void DesignerPage::onSize(wxSizeEvent& event)
{
	Refresh();
}

void DesignerPage::onMouse(wxMouseEvent& event)
{
	if (event.LeftDown()) 
	{
		m_lastpos.set(event.GetX(), event.GetY());

		Object* obj = DataConnection::m_currScene->queryByPoint(event.GetX() - m_origin.x, event.GetY() - m_origin.y);
		// order!!
		DataConnection::m_dstPanel->setObjectPage(obj);
		DataConnection::m_currObject = obj;
	}
	else if (event.RightDown())
	{
		deleteSelected();
		Refresh();
	}
	else if (event.Dragging())
	{
		if (DataConnection::m_currObject)
		{
			DataConnection::m_currObject->translate(event.GetX() - m_lastpos.x, event.GetY() - m_lastpos.y);
			DataConnection::m_dstPanel->setObjectPage(DataConnection::m_currObject);
			Refresh();
		}
		m_lastpos.set(event.GetX(), event.GetY());
	}
	else if (event.LeftUp() || event.RightUp())
	{
		VIEW::LIBRARY::ScenePage* page = dynamic_cast<VIEW::LIBRARY::ScenePage*>(DataConnection::m_libraryNotebook->GetPage(1));
		assert(page);
		page->updateThumbnail(*DataConnection::m_currScene);
	}
}

void DesignerPage::onKey(wxKeyEvent& event)
{
	switch (event.GetKeyCode())
	{
	case WXK_DELETE:
		deleteSelected();
		break;
	}
}

void DesignerPage::onPaint(wxPaintEvent& event)
{
	if (!DataConnection::m_currScene) return;

	updateOrigin();

	wxPaintDC dc(this);
	dc.Clear();

	DataConnection::m_currScene->onPaint(dc, m_origin);
}

void DesignerPage::updateOrigin()
{
	wxSize size = GetSize();
	m_origin.x = (int) (size.GetWidth() * 0.5f + 0.5f);
	m_origin.y = (int) (size.GetHeight() * 0.5f + 0.5f);
}

void DesignerPage::deleteSelected()
{
	if (DataConnection::m_currObject && DataConnection::m_currScene)
		DataConnection::m_currScene->deleteObject(DataConnection::m_currObject);
}

//////////////////////////////////////////////////////////////////////////
//	class DesignerPage::DragTileTarget
//////////////////////////////////////////////////////////////////////////

DesignerPage::DragTileTarget::DragTileTarget(DesignerPage* panel)
{
	m_panel = panel;
}

bool DesignerPage::DragTileTarget::OnDropText(wxCoord x, wxCoord y, const wxString& data)
{
	m_panel->addSprite(data, x, y);
	m_panel->Refresh();
	return true;
}