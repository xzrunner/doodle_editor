#include "ConditionPage.h"
#include "SrcPanel.h"
#include "Frame/Regulars/MousePress.h"

#include <wxGUI/wxGUI.h>

using namespace GAME_FRUITS;
using namespace GAME_FRUITS::VIEW::BACKSTAGE;

ConditionPage::ConditionPage(SrcPanel* parent)
	: SrcPageBase(parent)
{
	initFunctions();
	Connect(GetId(), wxEVT_COMMAND_LIST_BEGIN_DRAG, wxListEventHandler(ConditionPage::onDragInit));
	SetDropTarget(new wxgui::DragTargetNull);
}

void ConditionPage::initFunctions()
{
	InsertItem(*(new REGULAR::MousePress));
}

void ConditionPage::onDragInit(wxListEvent& event)
{
	wxTextDataObject tdo(GetItemText(event.GetIndex()));
	wxDropSource ds(tdo, this);
	ds.DoDragDrop(wxDrag_CopyOnly);
}