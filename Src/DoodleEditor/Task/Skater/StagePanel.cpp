#include "StagePanel.h"
#include "StageCanvas.h"

using namespace deditor::skater;

StagePanel::StagePanel(wxWindow* parent, wxgui::LibraryPanel* libraryPanel)
	: EditPanel(parent)
	, SpritesPanelImpl(this, libraryPanel)
	, ShapesPanelImpl(parent)
{
	m_canvas = new StageCanvas(this);
}

void StagePanel::insertSprite(wxgui::ISprite* sprite)
{
	wxgui::SpritesPanelImpl::insertSprite(sprite);

	if (!sprite->getUserData())
	{
		float* data = new float[4];
		data[0] = data[1] = 0.0f;
		data[2] = data[3] = 1.0f;
		sprite->setUserData(data);
	}
}

void StagePanel::insertShape(wxgui::IShape* shape)
{
	wxgui::ShapesPanelImpl::insertShape(shape);

	if (!shape->getUserData())
	{
		int* data = new int[1];
		data[0] = -1;
		shape->setUserData(data);
	}
}

void StagePanel::clear()
{
	wxgui::EditPanel::clear();
	wxgui::SpritesPanelImpl::clear();
	wxgui::ShapesPanelImpl::clear();
}