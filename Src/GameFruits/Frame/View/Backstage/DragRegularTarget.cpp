#include "DragRegularTarget.h"
#include "Frame/Regulars/ChangeImage.h"
#include "Frame/Regulars/ChangeScene.h"
#include "Frame/Regulars/ScaleSize.h"
#include "Frame/Regulars/MousePress.h"
#include "Frame/Regulars/Move.h"

using namespace GAME_FRUITS;
using namespace GAME_FRUITS::VIEW::BACKSTAGE;

DragRegularTarget::DragRegularTarget(wxWindow* parent)
{
	m_parent = parent;
}

RegularListItem* DragRegularTarget::createRegular(const wxString& name)
{
	RegularListItem* item = NULL;

	if (name == "Change Image")
		item = new REGULAR::ChangeImage;
	else if (name == "Change Scene")
		item = new REGULAR::ChangeScene;
	else if (name == "Size Scale")
		item = new REGULAR::ScaleSize;
	else if (name == "Mouse Press")
		item = new REGULAR::MousePress;
	else if (name == "Move")
		item = new REGULAR::Move;

	return item;
}