#include "AbstractView.h"
#include "ShortcutKeyListener.h"
#include "freeglut/freeglut.h"

using namespace FEDITOR;

AbstractView::AbstractView(float scale/* = 1.0f*/)
{
	m_scale = scale;
	m_camera = new Camera(scale);
	m_shortcutLsn = new ShortcutKeyListener;
}

AbstractView::~AbstractView()
{
	if (m_camera) delete m_camera;
	if (m_uiCtlsMgr) delete m_uiCtlsMgr;
	if (m_blackboard) delete m_blackboard;
	if (m_shortcutLsn) delete m_shortcutLsn;
}

void AbstractView::update()
{
	if (!m_uiCtlsMgr) return;

	std::queue<Event>& eventList = m_uiCtlsMgr->getEventList();
 	while (!eventList.empty())
 	{
 		Event event = eventList.front(); eventList.pop();
 		onUIEvent(event);
 	}

	m_cmptMgr.handleUIEvent();
}

void AbstractView::display(const LayersMgr& layers) const
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(
		m_camera->getLeft(), 
		m_camera->getLeft() + m_viewSize.viewWidth * m_camera->getScale(), 
		m_camera->getLow(),
		m_camera->getLow() + m_viewSize.viewHeight * m_camera->getScale()
		);

	onDraw(layers);
}

void AbstractView::createUIRoot(int mainWnd)
{
	if (m_uiCtlsMgr) m_uiCtlsMgr->createUIRoot(mainWnd);
}

void AbstractView::createUIControls()
{
	if (m_uiCtlsMgr) m_uiCtlsMgr->createUIControls(m_cmptMgr, m_shortcutLsn);
}

void AbstractView::onMouseWheel(int direction, int x, int y)
{
	const float newScale = direction > 0 ? m_camera->getScale() / 1.1f : m_camera->getScale() * 1.1f;
	const float cx = static_cast<float>(x),
		cy = static_cast<float>(m_viewSize.frameHeight - y);
	m_camera->onScale(newScale, cx, cy);
}

void AbstractView::reshape(int fw, int fh, int vw, int vh)
{
	m_viewSize.frameWidth = fw;
	m_viewSize.frameHeight = fh;
	m_viewSize.viewWidth = vw;
	m_viewSize.viewHeight = vh;

	setCameraPos(f2Vec2(0, 0));
}

f2Vec2 AbstractView::transPosScrToPoj(int x, int y) const
{
	return m_camera->transPosScrToPoj(x, y, m_viewSize.frameHeight);
}