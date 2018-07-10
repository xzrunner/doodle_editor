#ifndef _D2D_FILE_SYSTEM_H_
#define _D2D_FILE_SYSTEM_H_

#include "common/config.h"

#include <string>

namespace d2d
{
	class FileSystem
	{
	public:
		
		static FileSystem* Instance();

		std::string getAbsolutePath(const std::string& filename) const;

#ifdef D2D_WINDOWS
		void setWinRoot(const std::string& root) {
			m_winRoot = root;
		}
#endif // D2D_WINDOWS

#ifdef D2D_ANDROID_JNI
		void setResourcePath(const char *pszResourcePath);
		unsigned char* getFileData(const char* pszFileName, 
			const char* pszMode, unsigned long * pSize);
		unsigned char* getFileDataFromZip(const char* pszZipFilePath, 
			const char* pszFileName, unsigned long * pSize);
#endif // D2D_ANDROID_JNI

	protected:
		FileSystem() {}

	private:
		static FileSystem* m_instance;

#ifdef D2D_WINDOWS
		std::string m_winRoot;
#endif // D2D_WINDOWS

#ifdef D2D_ANDROID_JNI
		static std::string s_strResourcePath;
#endif // D2D_ANDROID_JNI

	}; // FileSystem
}

#endif // _D2D_FILE_SYSTEM_H_