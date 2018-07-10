#ifndef _WX_GUI_SPRITE_STAGE_CANVAS_H_
#define _WX_GUI_SPRITE_STAGE_CANVAS_H_

#include "GLCanvas.h"

#include "Render/SpriteBatch.h"

namespace wxgui
{
	class EditPanel;
	class MultiSpritesImpl;

	class SpriteStageCanvas : public GLCanvas
	{
	public:
		SpriteStageCanvas(EditPanel* editPanel, MultiSpritesImpl* spritesImpl);

	protected:
		virtual void onDraw();

	protected:
		MultiSpritesImpl* m_spritesImpl;

		SpriteBatch m_batch;

	}; // SpriteStageCanvas
}

#endif // _WX_GUI_SPRITE_STAGE_CANVAS_H_