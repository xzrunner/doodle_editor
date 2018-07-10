#include "main.h"
#include "Frame/MainFrame.h"

#include <wx/image.h>

using namespace FRUITS_ANIMATOR;

IMPLEMENT_APP(MyApp)

bool MyApp::OnInit()
{
	wxImage::AddHandler(new wxPNGHandler);

	MainFrame* frame = new MainFrame(wxT("FruitsAnimator"));
	frame->Show(true);

	return true;
}