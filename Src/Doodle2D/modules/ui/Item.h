#ifndef _D2D_ITEM_H_
#define _D2D_ITEM_H_

namespace d2d
{
	class Item
	{
	public:
		enum Type
		{
			e_actor = 0,
			e_button
		};

	public:
		Item(Type type) : m_type(type) {}

		virtual void onDraw() const = 0;

		Type type() const {
			return m_type;
		}

	private:
		Type m_type;

	}; // Item
}

#endif // _D2D_ITEM_H_