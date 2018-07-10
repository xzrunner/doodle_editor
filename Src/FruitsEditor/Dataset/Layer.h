#ifndef _FEDITOR_LAYER_H_
#define _FEDITOR_LAYER_H_
#include "../Render/LayerRenderStyle.h"

namespace FEDITOR
{
	class Sprite;

	class Layer : public ISerializable
	{
	public:
		enum Type
		{
			e_lowermost,
			e_middle,
			e_uppermost,
		};

		Layer(Type type);
		Layer(Type type, const std::string& name);
		~Layer();

		//
		// ISerializable interface
		//
		virtual void loadFromTextFile(std::ifstream& fin);
		virtual void storeToTextFile(std::ofstream& fout) const;

		void addSprite(Sprite* sprite);
		bool deleteSprite(Sprite* sprite);
		bool removeSprite(Sprite* sprite);
		void clearSprites();
		const std::vector<Sprite*>& getAllSprites() const;

		bool isVisible() const;
		void setVisible(bool visible);

		const std::string& getName() const;
		void setName(const std::string& name);
		Type getType() const;

		Sprite* queryByPos(const f2Vec2& pos, bool isAccurate = false) const;
		void queryByAABB(const f2AABB& aabb, std::vector<Sprite*>& sprites) const;

		void updateEachFrame();

		const f2Vec2& getOffset() const;
		void setOffset(const f2Vec2& offset);

	public:
		LayerRenderStyle m_style;

	private:
		std::string m_name;

		Type m_type;

		bool m_visible;

		f2Vec2 m_offset;

		std::vector<Sprite*> m_sprites;

	}; // Layer

	inline void Layer::addSprite(Sprite* sprite)
	{
		m_sprites.push_back(sprite);
	}

	inline const std::vector<Sprite*>& Layer::getAllSprites() const
	{
		return m_sprites;
	}

	inline bool Layer::isVisible() const
	{
		return m_visible;
	}

	inline void Layer::setVisible(bool visible)
	{
		m_visible = visible;
	}

	inline const std::string& Layer::getName() const
	{
		return m_name;
	}

	inline void Layer::setName(const std::string& name)
	{
		m_name = name;
	}

	inline Layer::Type Layer::getType() const
	{
		return m_type;
	}

	inline const f2Vec2& Layer::getOffset() const
	{
		return m_offset;
	}

	inline void Layer::setOffset(const f2Vec2& offset)
	{
		m_offset = offset;
	}
}

#endif // _FEDITOR_LAYER_H_