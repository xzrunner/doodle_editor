#ifndef _D2D_FRAME_ANIMATION_SPRITE_H_
#define _D2D_FRAME_ANIMATION_SPRITE_H_

#include "GraphicsSprite.h"
#include "modules/timer/TimeService.h"

namespace d2d
{
	class FrameAnimSprite : public GraphicsSprite
	{
	public:
		FrameAnimSprite(Texture* pTexture, int32_t pHeight, int32_t pWidth, Vector* pLocation);

		virtual void load();
		virtual void onDraw(float pTimeStep);

		void setAnimation(int32_t pStartFrame, int32_t pFrameCount, float pSpeed, bool pLoop);
		bool animationEnded();

	private:
//		void drawES11(int32_t lCurrentFrameX, int32_t lCurrentFrameY);
		void drawES20(int32_t lCurrentFrameX, int32_t lCurrentFrameY);

	private:
		Vector* m_location;

		// Frame.
		int32_t m_height, m_width;
		int32_t m_frameXCount, m_frameYCount, m_frameCount;

		// Animation.
		int32_t m_animStartFrame, m_animFrameCount;
		float m_animSpeed, m_animFrame;
		bool m_animLoop;

	}; // FrameAnimSprite
}

#endif // _D2D_FRAME_ANIMATION_SPRITE_H_