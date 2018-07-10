#ifndef _WX_GUI_IMAGE_H_
#define _WX_GUI_IMAGE_H_

#include "Tools/ResourcesMgr.h"

#include <wx/wx.h>

namespace wxgui
{
	class Image;
	typedef ResourcesMgr<Image> ImageMgr;

	class Image
	{
	public:
		Image();
		
		bool loadFromFile(const wxString& filepath);
		void reload() const;

		const wxString& filepath() const { return m_filepath; }

		unsigned int textureID() const { return m_textureID; }
		int width() const { return m_width; }
		int height() const { return m_height; }

		void draw() const;

	private:
		wxString m_filepath;

		mutable unsigned int m_textureID;
		int m_width, m_height;

	}; // Image
}

#endif // _WX_GUI_IMAGE_H_
