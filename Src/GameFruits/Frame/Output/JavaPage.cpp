#include "JavaPage.h"

using namespace GAME_FRUITS;
using namespace GAME_FRUITS::OUTPUT;

JavaPage::JavaPage(wxWindow* parent)
	: wxStyledTextCtrl(parent)
{
}

void JavaPage::storeToInterimData(InterimData& interim) const
{
	wxString totText = GetText();
}

void JavaPage::loadFromInterimData(const InterimData& interim)
{
	wxString totText;
	totText += "todo...\n";
	SetText(totText);
}