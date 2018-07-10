#ifndef _FEDITOR_ABSTRACT_VIEW_H_
#define _FEDITOR_ABSTRACT_VIEW_H_
#include "Utility.h"
#include "AbstractUICtrlsMgr.h"
#include "AbstractBlackboard.h"
#include "EditComponent/CmptMgr.h"
#include "../Tools/Camera.h"

class GLUI;

namespace FEDITOR
{
	class Camera;
	class LayersMgr;

	class AbstractView
	{
		struct ViewSize;

	public:
		AbstractView(float scale = 1.0f);
		virtual ~AbstractView();

		void update();

		void display(const LayersMgr& layers) const;

		void createUIRoot(int mainWnd);
		GLUI* getUIRoot() const;
		void createUIControls();

		AbstractBlackboard* getBlackboard() const;
		bool hasNextEvent() const;
		Event getNextEvent();

		void onMouseWheel(int direction, int x, int y);

		void reshape(int fw, int fh, int vw, int vh);

		f2Vec2 transPosScrToPoj(int x, int y) const;

		CmptMgr& getCmptMgr();

		float getScale() const;

		void setCameraPos(const f2Vec2& pos);

		const ShortcutKeyListener& getShortcutKeyLsn() const;

		void onModelEvent(const Event& event);

		const Camera& getCamera() const;
		const ViewSize& getViewSize() const;

	public:
		struct ViewSize
		{
			int frameWidth, frameHeight;
			int viewWidth, viewHeight;
		}; // ViewSize

	protected:
		virtual void onDraw(const LayersMgr& layers) const = 0;
		virtual void onUIEvent(const Event& event) = 0;

	protected:
		float m_scale;

		Camera* m_camera;
		ViewSize m_viewSize;

		AbstractUICtrlsMgr* m_uiCtlsMgr;

		AbstractBlackboard* m_blackboard;

		CmptMgr m_cmptMgr;

		ShortcutKeyListener* m_shortcutLsn;

	}; // AbstractView

	inline GLUI* AbstractView::getUIRoot() const
	{
		return m_uiCtlsMgr->getUIRoot();
	}

	inline AbstractBlackboard* AbstractView::getBlackboard() const
	{
		return m_blackboard;
	}

	inline bool AbstractView::hasNextEvent() const
	{
		return m_blackboard->hasNextEvent();
	}

	inline Event AbstractView::getNextEvent()
	{
		return m_blackboard->getNextEvent();
	}

	inline CmptMgr& AbstractView::getCmptMgr()
	{
		return m_cmptMgr;
	}

	inline float AbstractView::getScale() const
	{
		return m_scale;
	}

	inline void AbstractView::setCameraPos(const f2Vec2& pos)
	{
		m_camera->setCenter(pos, m_viewSize.viewWidth, m_viewSize.viewHeight);
	}

	inline const ShortcutKeyListener& AbstractView::getShortcutKeyLsn() const
	{
		return *m_shortcutLsn;
	}

	inline void AbstractView::onModelEvent(const Event& event)
	{
		m_uiCtlsMgr->onModelEvent(event);
	}

	inline const Camera& AbstractView::getCamera() const
	{
		return *m_camera;
	}

	inline const AbstractView::ViewSize& AbstractView::getViewSize() const
	{
		return m_viewSize;
	}
}

#endif // _FEDITOR_ABSTRACT_VIEW_H_