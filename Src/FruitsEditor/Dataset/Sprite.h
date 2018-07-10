#ifndef _FEDITOR_SPRITE_H_
#define _FEDITOR_SPRITE_H_
#include <Fruits2D/Fruits2D.h>
#include "Body.h"

namespace FEDITOR
{
	class Texture;
	class TextureRegion;
	class ColorRegion;
	class Shape;
	class Body;

	class Sprite : public IObject, public ISerializable
	{
	public:
		Sprite(float scale = 1.0f, BV_TYPE bvType = e_obb);
		Sprite(const Sprite& sprite);
		~Sprite();

		//
		// IObject interface
		//
		virtual Sprite* clone();

		//
		// ISerializable interface
		//
		virtual void loadFromTextFile(std::ifstream& fin);
		virtual void storeToTextFile(std::ofstream& fout) const;

		void loadFromUnknownFile(const std::string& filename);

		const std::string& getFilename() const;

		// Textures
		void pushTextureRegion(TextureRegion* textureRegion, bool refreshBounding = true);
		void clearTextureRegions();
		const std::vector<TextureRegion*>& getAllTextureRegions() const;

		void setTexture(Texture* texture);
		Texture* getTexture() const;

		// Shapes
		void pushShape(Shape* shape, bool refreshBounding = true);
		Shape* popShape();
		void clearShapes();
		const std::vector<Shape*>& getAllShapes() const;

		// Body
		void setBody(Body* body);
		Body* getBody() const;

		// Sprite setting
		const f2Vec2& getPosition() const;
		float getAngle() const;
		float getScale() const;
		float getXScale() const;
		float getYScale() const;
		f2Vec2 transToLocalPosition(const f2Vec2& pos) const;

		void translate(const f2Vec2& offset);
		void rotate(float delta);
		void setTransform(const f2Vec2& position, float angle);
		void setScale(float xScale, float yScale, bool updatePhysAndAABB = false);

		F2D::AbstractBV* getBounding() const;
		void rebuildBounding();

		void updateEachFrame();

		bool isContain(const f2Vec2& pos, bool isAccurate = false) const;
		bool isIntersect(const f2AABB& aabb) const;

		void setUserData(void* data);
		void* getUserData() const;

	private:
		void loadFromImgFile(const std::string& filename);
		void loadFromLoopsFile(const std::string& filename);
		void loadFromChainsFile(const std::string& filename);
		void loadFromCircleFile(const std::string& filename);

	private:
		template<class T>
		class Container
		{
		public:
// 			~Container() {
// 				std::cout << "Container destruct" << std::endl;
// 			}

			void storeToTextFile(std::ofstream& fout) const;

			void push(T* entry);
			T* pop();
			void clear();
			const std::vector<T*>& getAll() const;

			size_t size() const;
			void reserve(size_t size);
			const T* operator[](size_t index) const;

			void getAABB(f2AABB& aabb, const f2Vec2& position, float angle) const;

		private:
			std::vector<T*> m_data;

		}; // Container

		typedef Container<TextureRegion> TextureRegionList;
		typedef Container<Shape> ShapeList;

	private:
		std::string m_filename;

		TextureRegionList m_textureRegions;
		ShapeList m_shapes;

		f2Vec2 m_position;
		float m_angle;				// in radian
		float m_xScale, m_yScale;

		Body* m_body;

		F2D::AbstractBV* m_bounding;

		Texture* m_texture;

		void* m_userData;

	}; // Sprite

	template<class T>
	inline void Sprite::Container<T>::storeToTextFile(std::ofstream& fout) const
	{
		fout << m_data.size() << '\n';
		for (size_t i = 0, n = m_data.size(); i < n; ++i)
			m_data[i]->storeToTextFile(fout);
	}

	template<class T>
	inline void Sprite::Container<T>::push(T* entry)
	{
		m_data.push_back(entry);
	}

	template<class T>
	inline T* Sprite::Container<T>::pop()
	{
		if (m_data.empty())
		{
			return NULL;
		}
		else
		{
			T* item = m_data.back();
			m_data.pop_back();
			return item;
		}
	}

	template<class T>
	inline void Sprite::Container<T>::clear()
	{
		for_each(m_data.begin(), m_data.end(), DeletePointerFunctor<T>());
		m_data.clear();
	}

	template<class T>
	inline const std::vector<T*>& Sprite::Container<T>::getAll() const
	{
		return m_data;
	}

	template<class T>
	inline size_t Sprite::Container<T>::size() const
	{
		return m_data.size();
	}

	template<class T>
	inline void Sprite::Container<T>::reserve(size_t size)
	{
		m_data.reserve(size);
	}

	template<class T>
	inline const T* Sprite::Container<T>::operator[](size_t index) const
	{
		return m_data[index];
	}

	template<class T>
	inline void Sprite::Container<T>::getAABB(f2AABB& aabb, const f2Vec2& position, float angle) const
	{
		aabb.makeInfinite();
		for (size_t i = 0, n = m_data.size(); i < n; ++i)
		{
			f2AABB r;
			m_data[i]->getAABB(r, position, angle);
			aabb.combine(r);
		}
	}

	inline const std::vector<TextureRegion*>& Sprite::getAllTextureRegions() const 
	{ 
		return m_textureRegions.getAll(); 
	}

	inline void Sprite::setTexture(Texture* texture)
	{
		m_texture = texture;
	}

	inline Texture* Sprite::getTexture() const
	{
		return m_texture;
	}

	inline const std::vector<Shape*>& Sprite::getAllShapes() const 
	{ 
		return m_shapes.getAll(); 
	}

	inline void Sprite::setBody(Body* body)
	{
		if (m_body) delete m_body;
		m_body = body;
	}

	inline Body* Sprite::getBody() const
	{
		return m_body;
	}

	inline const f2Vec2& Sprite::getPosition() const
	{
		return m_position;
	}

	inline float Sprite::getAngle() const
	{
		return m_angle;
	}

	inline float Sprite::getScale() const
	{
		return fabs(m_xScale);
	}

	inline float Sprite::getXScale() const
	{
		return m_xScale;
	}

	inline float Sprite::getYScale() const
	{
		return m_yScale;
	}

	inline F2D::AbstractBV* Sprite::getBounding() const
	{
		return m_bounding;
	}

	inline void Sprite::setUserData(void* data)
	{
		delete m_userData;
		m_userData = data;
	}

	inline void* Sprite::getUserData() const
	{
		return m_userData;
	}
}

#endif // _FEDITOR_SPRITE_H_