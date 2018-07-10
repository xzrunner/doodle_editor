#ifndef _DEDITOR_TEXTURE_EDIT_PARTITION_IMAGE_H_
#define _DEDITOR_TEXTURE_EDIT_PARTITION_IMAGE_H_

#include <wx/wx.h>

namespace deditor
{
	namespace texture_edit
	{
		class PartitionImage
		{
		public:
			static void partition(const wxString& filepath,
				size_t row, size_t col);

		}; // PartitionImage
	}
}

#endif // _DEDITOR_TEXTURE_EDIT_PARTITION_IMAGE_H_