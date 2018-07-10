#ifndef _DEDITOR_COMPRESS_PICTURE_COMPRESS_PICTURE_H_
#define _DEDITOR_COMPRESS_PICTURE_COMPRESS_PICTURE_H_

#include <wx/wx.h>

namespace deditor
{
	namespace compress_pictures
	{
		struct CompressParams
		{
			int m_jpgQuality;
			int m_pngColors, m_pngSpeed;
		};

		class CompressPicture
		{
		public:
			CompressPicture(const CompressParams& params,
				const wxString& src, const wxString& dst);

			void compress() const;

		private:
			void compressJpeg() const;
			void compressPng() const;

		private:
			const CompressParams& m_params;

			const wxString &m_src, &m_dst;

		}; // CompressPicture
	}
}

#endif // _DEDITOR_COMPRESS_PICTURE_COMPRESS_PICTURE_H_