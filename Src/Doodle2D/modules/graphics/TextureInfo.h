#ifndef _D2D_TEXTURE_INFO_H_
#define _D2D_TEXTURE_INFO_H_

#include "common/types.h"
#include "common/Vector.h"

#include <vector>
#ifdef D2D_ANDROID_NATIVE
#	include <android_native_app_glue.h>
#	include <string>
#elif defined D2D_ANDROID_JNI
#	include <string>
#endif

namespace d2d
{
	class Texture;

	class TextureInfo
	{
	public:
		struct Region
		{
			int left;
			int top;
			int width;
			int height;

			std::vector<std::vector<Vector> > loops;

			Region()
				: left(0), top(0), width(0), height(0) {}
			Region(int l, int t, int w, int h) 
				: left(l), top(t), width(w), height(h) {}
		};

	public:
		TextureInfo(bool hasBoundaryInfo);
		~TextureInfo();

		void setTexture(Texture* texture) { m_texture = texture; }
		Texture* getTexture() const { return m_texture; }

		void setSizer(int width, int height);
		int getWidth() const { return m_width; }
		int getHeight() const { return m_height; }

		void addRegion(int left, int top, int width, int height);
		const Region* getRegion(int index) const;

		size_t regionSize() const { return m_regions.size(); }

		void loadFromMemory(byte** ptr);
#ifdef D2D_WINDOWS
		void loadFromFile(const std::string& filepath);
#elif defined D2D_ANDROID_NATIVE
		void loadFromFile(android_app* pApplication, const std::string& filepath);
#elif defined D2D_ANDROID_JNI
		void loadFromFile(const std::string& filepath);
#endif

	private:
		void clear();

		void loadBoundary(byte** ptr, Region* region);
		void loadPolygonInfo(byte** ptr, Region* region);
		void loadCircleInfo(byte** ptr, Region* region);

	private:
		Texture* m_texture;

		bool m_hasBoundaryInfo;

		int m_width, m_height;
		std::vector<Region*> m_regions;

	}; // TextureInfo
}

#endif // _D2D_TEXTURE_INFO_H_