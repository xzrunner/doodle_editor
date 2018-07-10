#include "ActionPage.h"
#include "SrcPanel.h"
#include "Frame/Regulars/ChangeImage.h"
#include "Frame/Regulars/ChangeScene.h"
#include "Frame/Regulars/ScaleSize.h"

#include <wxGUI/wxGUI.h>

using namespace GAME_FRUITS;
using namespace GAME_FRUITS::VIEW::BACKSTAGE;

ActionPage::ActionPage(SrcPanel* parent)
	: SrcPageBase(parent)
{
	initFunctions();
	Connect(GetId(), wxEVT_COMMAND_LIST_BEGIN_DRAG, wxListEventHandler(ActionPage::onDragInit));
	SetDropTarget(new wxgui::DragTargetNull);
}

void ActionPage::initFunctions()
{
	InsertItem(*(new REGULAR::ChangeImage));
	InsertItem(*(new REGULAR::ChangeScene));
	InsertItem(*(new REGULAR::ScaleSize));
}

void ActionPage::onDragInit(wxListEvent& event)
{
	wxTextDataObject tdo(GetItemText(event.GetIndex()));
	wxDropSource ds(tdo, this);
	ds.DoDragDrop(wxDrag_CopyOnly);
}