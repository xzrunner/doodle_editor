#include "Settings.h"

using namespace wxgui;

bool Settings::bZoomOnlyUseMouseWheel = true;

int Settings::ctlPosSize = 0;
bool Settings::bDisplayTrisEdge = false;
bool Settings::bDisplayPolyBound = true;

Settings::DrawType Settings::drawType = e_DrawBoth;

std::set<wxString> Settings::RESOURCE_PATH;