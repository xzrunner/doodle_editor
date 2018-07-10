#include "XRCPage.h"

using namespace GAME_FRUITS;
using namespace GAME_FRUITS::OUTPUT;

XRCPage::XRCPage(wxWindow* parent)
	: wxStyledTextCtrl(parent)
{
}

void XRCPage::storeToInterimData(InterimData& interim) const
{
	wxString totText = GetText();
}

void XRCPage::loadFromInterimData(const InterimData& interim)
{
	wxString totText;
	totText += "todo...\n";
	SetText(totText);
}