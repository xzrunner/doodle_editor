#include "main.h"
#include "Frame/Frame.h"

#include <wx/image.h>

using namespace GAME_FRUITS;

IMPLEMENT_APP(MyApp)

bool MyApp::OnInit()
{
	wxImage::AddHandler(new wxPNGHandler);

	Frame* frame = new Frame(wxT("GameFruits"));
	frame->Show(true);

	return true;
}