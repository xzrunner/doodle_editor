#ifndef _FEDITOR_ARRANGE_SPRITE_COMMON_OPERATION_H_
#define _FEDITOR_ARRANGE_SPRITE_COMMON_OPERATION_H_
#include "ArrangeSpritePhysOp.h"

class b2World;
class b2Body;

namespace FEDITOR
{
	class Layer;
	class ArrangeSpriteOp;
	class ArrangeSpritePhysOp;
	class AbstractArrangeSpriteCB;

	class ArrangeSpriteCommonOp : public AbstractOp
	{
	public:
		ArrangeSpriteCommonOp(AbstractControl* task, Layer* editable, b2World* world, b2Body* ground, 
			int physQueryType = ArrangeSpritePhysOp::e_MouseOn, AbstractArrangeSpriteCB* callback = NULL,
			AbstractOp* supplement = NULL);

		virtual void onKeyboard(unsigned char key);
		virtual void onMouseLeftDown(int x, int y);
		virtual void onMouseLeftUp(int x, int y);
		virtual bool onMouseRightDown(int x, int y);
		virtual bool onMouseRightUp(int x, int y);
		virtual void onMouseDrag(int x, int y);

		b2World* getWorld() const;

	private:
		void initOp(const f2Vec2& pos);

	private:
		Layer* m_editable;

		b2World* m_world;
		b2Body* m_ground;
		int m_queryType;

		AbstractArrangeSpriteCB* m_callback;
		AbstractOp* m_supplement;

		ArrangeSpriteOp* m_noPhysOp;
		ArrangeSpritePhysOp* m_physOp;

	}; // ArrangeSpriteCommonOp
}

#endif // _FEDITOR_ARRANGE_SPRITE_COMMON_OPERATION_H_