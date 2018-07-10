#ifndef _WX_GUI_RAW_PIXELS_H_
#define _WX_GUI_RAW_PIXELS_H_

#include <Fruits2D/Fruits2D.h>

namespace wxgui
{
	class RawPixels
	{
	public:
		RawPixels();
		~RawPixels();

 		void loadFromFile(const char* filepath);
// 		unsigned int storeToTexture(unsigned int old) const;

		const unsigned char* getPixelData() const;
		void getSize(int& width, int& height) const;
		int getChannels() const;

	public:
		struct PixelsPos
		{
			int x, y;
		}; // PixelsPos

		class PixelCmp
		{
		public:
			bool operator () (const PixelsPos* lhs, const PixelsPos* rhs) const {
				return lhs->x < rhs->x
					|| lhs->x == rhs->x && lhs->y < rhs->y;
			}
		}; // PixelCmp

		typedef std::set<PixelsPos*, PixelCmp> PixelBuf;

		void replaceBySelected(const PixelBuf& selected);

	private:
		unsigned char* m_pixelData;
		int m_width, m_height, m_channels;

	}; // RawPixels
}

#endif // _WX_GUI_RAW_PIXELS_H_