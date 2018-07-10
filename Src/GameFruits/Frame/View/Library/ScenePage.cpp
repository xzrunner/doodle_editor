#include "ScenePage.h"
#include "Dataset/DataConnection.h"
#include "Dataset/Scene.h"
#include "Frame/View/Backstage/DstPanel.h"
#include <wx/listctrl.h>

using namespace GAME_FRUITS;
using namespace GAME_FRUITS::VIEW::LIBRARY;

ScenePage::ScenePage(wxWindow* parent)
	: LibraryPageBase(parent)
{
	initLayout();

	Connect(m_add->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(ScenePage::onAddScene));
	Connect(m_del->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(ScenePage::onDelScene));
	Connect(m_listCtrl->GetId(), wxEVT_COMMAND_LIST_ITEM_SELECTED, wxListEventHandler(ScenePage::onListItemSelected));

	add(DataConnection::m_currScene);
}

void ScenePage::setName(const wxString& from, const wxString& to)
{
	int index = m_listCtrl->FindItem(-1, from);
	m_listCtrl->SetItemText(index, to);
}

void ScenePage::updateThumbnail(const Scene& scene)
{
	int imgID = queryImageID(scene.getName());
	assert(imgID != -1);

	wxMemoryDC memDC;
	wxBitmap bitmap(IMG_WIDTH, IMG_HEIGHT);
	memDC.SelectObject(bitmap);
	scene.onPaint(memDC, 0.1f);
	memDC.SelectObject(wxNullBitmap);

	m_imageList->Replace(imgID, bitmap);	
	Refresh();
}

void ScenePage::initLayout()
{
	m_imageList = new wxImageList(80, 48);
//	m_listCtrl->SetWindowStyle(wxLC_LIST | wxLC_SINGLE_SEL);
	m_listCtrl->SetImageList(m_imageList, wxIMAGE_LIST_NORMAL);

	m_listCtrl->SetSingleStyle(wxLC_SINGLE_SEL | wxLC_AUTOARRANGE, true);
	m_listCtrl->SetSingleStyle(wxLC_LIST, false);
}

void ScenePage::onAddScene(wxCommandEvent& event)
{
	Scene* scene = new Scene(DataConnection::m_game.m_width, DataConnection::m_game.m_height);
	DataConnection::m_game.m_scenes.push_back(scene);
	add(scene);
	updateListeners();
}

void ScenePage::onDelScene(wxCommandEvent& event)
{
	int count = m_listCtrl->GetItemCount();
	if (count <= 1) return;

	long item = -1;
	while (true)
	{
		item = m_listCtrl->GetNextItem(item, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
		if (item == -1)
			break;

		DataConnection::m_game.deleteScene(m_listCtrl->GetItemText(item));
		m_listCtrl->DeleteItem(item);
	}

	wxListItem info;
	info.SetId(m_listCtrl->GetNextItem(-1));
	info.SetState(wxLIST_STATE_FOCUSED | wxLIST_STATE_SELECTED);
	m_listCtrl->SetItem(info);

	updateListeners();
}

void ScenePage::onListItemSelected(wxListEvent& event)
{
	Scene* scene = DataConnection::m_game.queryScene(m_listCtrl->GetItemText(event.m_itemIndex));
	assert(scene);
	DataConnection::m_currScene = scene;
	DataConnection::m_dstPanel->setScenePage(scene);
	DataConnection::m_stage->Refresh();
}

void ScenePage::add(Scene* scene)
{
	wxImage img(IMG_WIDTH, IMG_HEIGHT);
	const wxColour& color = scene->getColor();
	img.SetRGB(wxRect(0, 0, IMG_WIDTH, IMG_HEIGHT), color.Red(), color.Green(), color.Blue());

	wxBitmap bitmap(img);
	m_imageList->Add(bitmap);

	int itemSize = m_listCtrl->GetItemCount();

	wxListItem *item = new wxListItem;
	item->SetState(wxLIST_STATE_FOCUSED | wxLIST_STATE_SELECTED | wxLIST_MASK_IMAGE);
	item->SetText(scene->getName());
	item->SetImage(itemSize);

	m_listCtrl->InsertItem(*item);
}

int ScenePage::queryImageID(const wxString& item)
{
	long itemID = -1;
	while (true)
	{
		itemID = m_listCtrl->GetNextItem(itemID);
		if (itemID == -1)
			break;

		wxListItem info;
		info.SetId(itemID);
		info.SetMask(wxLIST_MASK_TEXT | wxLIST_MASK_IMAGE);
		m_listCtrl->GetItem(info);

		if (info.GetText() != item) continue;

		return info.GetImage();
	}
	return -1;
}