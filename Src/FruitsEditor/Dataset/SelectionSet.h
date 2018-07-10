#ifndef _FEDITOR_SELECTION_SET_H_
#define _FEDITOR_SELECTION_SET_H_
#include <Fruits2D/Fruits2D.h>

namespace FEDITOR
{
	class Sprite;

	class SelectionSet
	{
	public:
		bool empty() const;

		void add(Sprite* sprite);
		void erase(Sprite* sprite);
		void clear();

		Sprite* getSingle() const;
		const std::set<Sprite*>& getAll() const;

		bool exist(Sprite* sprite) const;

	private:
		std::set<Sprite*> m_sprites;

	}; // SelectionSet

	inline bool SelectionSet::empty() const
	{
		return m_sprites.empty();
	}

	inline void SelectionSet::add(Sprite* sprite)
	{
		m_sprites.insert(sprite);
	}

	inline void SelectionSet::erase(Sprite* sprite)
	{
		std::set<Sprite*>::iterator itr = m_sprites.find(sprite);
		if (itr != m_sprites.end())
			m_sprites.erase(itr);
	}

	inline void SelectionSet::clear()
	{
		m_sprites.clear();
	}

	inline Sprite* SelectionSet::getSingle() const
	{
		if (m_sprites.size() != 1)
			return NULL;
		else 
			return *m_sprites.begin();
	}

	inline const std::set<Sprite*>& SelectionSet::getAll() const
	{
		return m_sprites;
	}

	inline bool SelectionSet::exist(Sprite* sprite) const
	{
		return m_sprites.find(sprite) != m_sprites.end();
	}
}

#endif // _FEDITOR_SELECTION_SET_H_