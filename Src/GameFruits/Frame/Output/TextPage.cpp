#include "TextPage.h"

using namespace GAME_FRUITS;
using namespace GAME_FRUITS::OUTPUT;

TextPage::TextPage(wxWindow* parent)
	: wxStyledTextCtrl(parent)
{
}

void TextPage::storeToInterimData(InterimData& interim) const
{
	wxString totText = GetText();
}

void TextPage::loadFromInterimData(const InterimData& interim)
{
	wxString totText;
	totText += "todo...\n";
	SetText(totText);
}