#include "SrcPanel.h"
#include "ConditionPage.h"
#include "PersistentPage.h"
#include "ActionPage.h"

using namespace GAME_FRUITS::VIEW::BACKSTAGE;

SrcPanel::SrcPanel(wxWindow* parent)
	: wxNotebook(parent, wxID_ANY)
{
	AddPage(new ConditionPage(this), wxT("Conditions"));
	AddPage(new PersistentPage(this), wxT("Persistent"));
	AddPage(new ActionPage(this), wxT("Actions"));
}