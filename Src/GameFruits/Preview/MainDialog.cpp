#include "MainDialog.h"
#include "Scene.h"

using namespace GAME_FRUITS::PREVIEW;

BEGIN_EVENT_TABLE(MainDialog, wxDialog)
	EVT_MOUSE_EVENTS(MainDialog::onMouse)
	EVT_PAINT(MainDialog::onPaint)
END_EVENT_TABLE()

MainDialog::MainDialog(wxWindow* parent)
	: wxDialog(parent, wxID_ANY, "Preview",
	wxDefaultPosition, wxSize(800, 480),
	wxCLOSE_BOX | wxCAPTION)
{
	m_scene = NULL;
}

MainDialog::~MainDialog()
{
	delete m_scene;
}

void MainDialog::loadFromScene(GAME_FRUITS::Scene* scene)
{
	if (m_scene) delete m_scene;
	m_scene = new Scene(this, scene);
	Refresh();
}

void MainDialog::onMouse(wxMouseEvent& event)
{
	if (event.LeftDown())
		m_scene->onMouseDown(event.GetX(), event.GetY());
	else if (event.LeftUp())
		m_scene->onMouseUp(event.GetX(), event.GetY());
}

void MainDialog::onPaint(wxPaintEvent& event)
{
	wxPaintDC dc(this);
	m_scene->onPaint(dc);
}