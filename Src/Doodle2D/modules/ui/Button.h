#ifndef _D2D_BUTTON_H_
#define _D2D_BUTTON_H_

#include "Item.h"

#include <vector>

namespace d2d
{
	class GraphicsSprite;
	class Behavior;
	class Vector;

	class Button : public Item
	{
	public:
		Button(GraphicsSprite* sprite);
		~Button();

		virtual void onDraw() const;

		bool isContain(const Vector& pos) const;

		void addBehavior(Behavior* behavior, bool bPress);
		void triggerBehaviors(bool bPress);

	private:
		GraphicsSprite* m_sprite;

		std::vector<Behavior*> m_pressBehaviors;
		std::vector<Behavior*> m_liftBehaviors;

	}; // Button
}

#endif // _D2D_BUTTON_H_