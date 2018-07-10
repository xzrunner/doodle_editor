#ifndef _FEDITOR_IMG_FILE_ADAPTER_H_
#define _FEDITOR_IMG_FILE_ADAPTER_H_
#include "TextFileAdapter.h"

namespace FEDITOR
{
	class Sprite;

	class ImgFileAdapter : public TextFileAdapter
	{
	public:
		ImgFileAdapter();

		virtual void load(const std::string& filename);

	public:
		Sprite* m_sprite;

	}; // ImgFileAdapter
}

#endif // _FEDITOR_IMG_FILE_ADAPTER_H_