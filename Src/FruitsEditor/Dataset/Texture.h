#ifndef _FEDITOR_TEXTURE_H_
#define _FEDITOR_TEXTURE_H_
#include "../Tools/ResourcesMgr.h"

namespace FEDITOR
{
	class Texture;
	typedef ResourcesMgr<Texture> TexturesMgr;

	class Texture
	{
	public:
		bool isValid() const;

		int getTexID() const;

		std::string getFilename(bool avoidExtension = false) const;

		float getWidth() const;
		float getHeight() const;

	private:
		Texture();

		bool loadFromFile(const std::string& filename);

	private:
		std::string m_filename;
		int m_id;
		float m_width, m_height;

		friend class ResourcesMgr<Texture>;

	}; // Texture

	

	inline Texture::Texture() 
		: m_id(0), m_width(0), m_height(0)
	{
	}

	inline bool Texture::isValid() const
	{
		return m_id != 0;
	}

	inline int Texture::getTexID() const
	{
		return m_id;
	}

	inline std::string Texture::getFilename(bool avoidExtension/* = false*/) const
	{
		return avoidExtension ? m_filename.substr(0, m_filename.find_last_of('.')) : m_filename;
	}

	inline float Texture::getWidth() const
	{
		return m_width;
	}

	inline float Texture::getHeight() const
	{
		return m_height;
	}

}

#endif // _FEDITOR_TEXTURE_H_