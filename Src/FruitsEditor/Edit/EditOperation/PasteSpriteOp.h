#ifndef _FEDITOR_PASTE_SPRITE_OPERATION_H_
#define _FEDITOR_PASTE_SPRITE_OPERATION_H_
#include "AbstractOp.h"

namespace FEDITOR
{
	class Layer;
	class Sprite;
	class IPasteSpriteCB;

	class PasteSpriteOp : public AbstractOp
	{
	public:
 		PasteSpriteOp(AbstractControl* task, Layer* templayer, Layer* dstLayer,
 			const std::string& filename, bool toInteger = false, IPasteSpriteCB* callback = NULL, 
 			float xScale = 1.0f, float yScale = 1.0f, int batchNum = 0, int batchRadius = 0);
		~PasteSpriteOp();

		virtual void onMouseLeftDown(int x, int y);
		virtual bool onMouseRightDown(int x, int y);
		virtual void onMouseMove(int x, int y);
		virtual void onMouseDrag(int x, int y);

	private:
		void addSprite(f2Vec2& pos, float angle);

	private:
		IPasteSpriteCB* m_callback;

		std::string m_filename;
		float m_xScale, m_yScale;

		int m_batchNum, m_batchRadius;

		Layer *m_templayer, *m_dstLayer;
		Sprite* m_sprite;

		bool m_toInteger;

	}; // PasteSpriteOp
}

#endif // _FEDITOR_PASTE_SPRITE_OPERATION_H_