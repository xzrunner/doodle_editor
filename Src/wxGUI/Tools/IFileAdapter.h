#ifndef _WX_GUI_INTERFACE_FILE_ADAPTER_H_
#define _WX_GUI_INTERFACE_FILE_ADAPTER_H_

namespace wxgui
{
	class IFileAdapter
	{
	public:
		virtual ~IFileAdapter() {}

		virtual void load(const char* filename) = 0;
		virtual void store(const char* filename) {}

	}; // IFileAdapter
}

#endif // _WX_GUI_INTERFACE_FILE_ADAPTER_H_