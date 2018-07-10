#include "PreviewGLCanvas.h"
#include "LibraryPanel.h"
#include "Dataset/Mesh.h"
#include "Dataset/PartSkeleton.h"
#include "Dataset/WholeSkeleton.h"
#include "Dataset/Sprite.h"
#include "Dataset/KeyFrame.h"
#include "Dataset/Layer.h"
#include "Dataset/LayersMgr.h"
#include "Tools/Render.h"

using namespace FRUITS_ANIMATOR;

BEGIN_EVENT_TABLE(PreviewGLCanvas, wxgui::GLCanvas)
	EVT_TIMER(TIMER_ID, PreviewGLCanvas::onTimer)
END_EVENT_TABLE()

PreviewGLCanvas::PreviewGLCanvas(wxgui::EditPanel* editPanel, LayersMgr* layers, 
								 LibraryPanel* library, int fps/* = 24*/)
	: wxgui::GLCanvas(editPanel)
	, m_timer(this, TIMER_ID)
{
	m_layersMgr = layers;

	m_library = library;

	m_timer.Start(1000 / fps);
	m_currFrame = 1;
}

PreviewGLCanvas::PlaySetting& PreviewGLCanvas::getPlaySetting()
{
	return m_setting;
}

void PreviewGLCanvas::initGL()
{
	wxgui::GLCanvas::initGL();
	m_library->reloadAllTexture();
}

void PreviewGLCanvas::onDraw()
{
	drawStageData();
}

void PreviewGLCanvas::onTimer(wxTimerEvent& event)
{
	if (!m_setting.isStop)
		++m_currFrame;

	if (m_currFrame > m_layersMgr->getFrameCount())
	{
		if (m_setting.isCirculate) m_currFrame = 1;
		else --m_currFrame;
	}

	Refresh();
}

void PreviewGLCanvas::drawStageData()
{
	std::vector<Sprite*> sprites;
	getCurrSprites(sprites);
	Render::drawSprites(sprites);
	for_each(sprites.begin(), sprites.end(), DeletePointerFunctor<f2Sprite>());
}

void PreviewGLCanvas::getCurrSprites(std::vector<Sprite*>& sprites) const
{
	for (size_t i = 0, n = m_layersMgr->size(); i < n; ++i)
	{
		Layer* layer = m_layersMgr->getLayer(i);

		KeyFrame *currFrame = layer->getCurrKeyFrame(m_currFrame),
			*nextFrame = layer->getNextKeyFrame(m_currFrame);
		if (!currFrame->hasClassicTween() || !nextFrame)
		{
			const std::vector<Sprite*>& all = currFrame->getAllSprites();
			for (size_t i = 0, n = all.size(); i < n; ++i)
				sprites.push_back(all[i]->clone());
		}
		else
		{
			assert(m_currFrame >= currFrame->getTime() && m_currFrame < nextFrame->getTime());
			float process = (float) (m_currFrame - currFrame->getTime()) / (nextFrame->getTime() - currFrame->getTime());
			getTweenSprites(currFrame->getAllSprites(), nextFrame->getAllSprites(), sprites, process);
		}
	}
}

void PreviewGLCanvas::getTweenSprites(const std::vector<Sprite*>& start, const std::vector<Sprite*>& end, 
									  std::vector<Sprite*>& tween, float process) const
{
	for (size_t i = 0, n = start.size(); i < n; ++i)
	{
		Sprite *startSprite = start[i], *endSprite = NULL;
		for (size_t j = 0, m = end.size(); j < m; ++j)
		{
			if (isTweenMatched(*startSprite, *end[j]))
			{
				endSprite = end[j];
				break;
			}
		}

		if (endSprite)
		{
			Sprite* tweenSprite = startSprite->clone();
			getTweenSprite(startSprite, endSprite, tweenSprite, process);
			tween.push_back(tweenSprite);
		}
		else
		{
			tween.push_back(startSprite->clone());
		}
	}
}

bool PreviewGLCanvas::isTweenMatched(Sprite& s0, Sprite& s1) const
{
	if (s0.getWholeSkeleton() && s1.getWholeSkeleton())
	{
		return s0.getWholeSkeleton()->getName() == s1.getWholeSkeleton()->getName();
	}
	else
	{
		return s0.getSymbol() == s1.getSymbol();
	}
}

void PreviewGLCanvas::getTweenSprite(Sprite* start, Sprite* end, Sprite* tween, float process) const
{
	f2Vec2 offset = (end->getPosition() - start->getPosition()) * process;
	float delta = (end->getAngle() - start->getAngle()) * process;
	tween->translate(offset);
	tween->rotate(delta);

	if (start->getSymbol() == end->getSymbol())
	{
		if (start->getMesh() && end->getMesh())
			tween->getMesh()->tween(*start->getMesh(), *end->getMesh(), process);
		else if (start->getPartSkeleton() && end->getPartSkeleton())
			tween->getPartSkeleton()->tween(*start->getPartSkeleton(), *end->getPartSkeleton(), process);
		else if (start->getWholeSkeleton() && end->getWholeSkeleton())
			tween->getWholeSkeleton()->tween(*start->getWholeSkeleton(), *end->getWholeSkeleton(), process);
	}
}