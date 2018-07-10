#include "LayersIOCmpt.h"
#include "CmptTypeID.h"
#include "glui/glui.h"

using namespace FEDITOR;

GLUI_FileBrowser* LayersIOCmpt::m_layers_fb = NULL;

std::queue<Event> LayersIOCmpt::m_eventList;

LayersIOCmpt::LayersIOCmpt(const LayersMgr& layers, CmptMgr& cmptMgr, const std::string& filename)
	: AbstractCmpt(e_LayersIOCmpt, cmptMgr), m_layers(layers)
{
}

void LayersIOCmpt::createUIControls(GLUI_Node* parent, ShortcutKeyListener* shortcutLsn)
{
	GLUI_Rollout* panel = new GLUI_Rollout(parent, "Layers I/O", false);

	m_layers_fb = new GLUI_FileBrowser(panel, "", false, e_OpenFromFile, callback);
	new GLUI_Button(panel, "Save", e_StoreToFile, callback);
}

void LayersIOCmpt::handleUIEvent()
{
	while (!m_eventList.empty())
	{
		Event event = m_eventList.front(); m_eventList.pop();
		switch (event.getID())
		{
		}
	}
}

void LayersIOCmpt::callback(int id)
{
	switch (id)
	{
	case e_OpenFromFile:
		m_eventList.push(Event(id, m_layers_fb->get_file()));
		break;
	default:
		m_eventList.push(Event(id));
	}
}