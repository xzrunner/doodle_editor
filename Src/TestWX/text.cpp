#include "text.h"


Text::Text(const wxString& title)
: wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(250, 150))
{
	Connect(wxEVT_PAINT, wxPaintEventHandler(Text::OnPaint));
	Centre();
}

void Text::OnPaint(wxPaintEvent& event)
{
	wxPaintDC dc(this);

	dc.DrawText(wxT("§­§Ö§Ó §¯§Ú§Ü§à§Ýa§Ö§Ó§Ú§é §´§à§Ý§ã§äo§Û"), 40, 60);
	dc.DrawText(wxT("§¡§ß§ß§Ñ §¬§Ñ§â§Ö§ß§Ú§ß§Ñ"), 70, 80);
}