#include "main.h"
#include "Frame/Frame.h"

#include <wx/image.h>

using namespace deditor;

IMPLEMENT_APP(MyApp)

bool MyApp::OnInit()
{
	wxImage::AddHandler(new wxPNGHandler);

	Frame* frame = new Frame(wxT("DoodleEditor"));
	frame->Show(true);

	return true;
}