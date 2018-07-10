#include "FileSystem.h"

#ifdef D2D_ANDROID_JNI
#include <Minizip/unzip.h>
#endif // D2D_ANDROID_JNI

using namespace d2d;

FileSystem* FileSystem::m_instance = NULL;
#ifdef D2D_ANDROID_JNI
std::string FileSystem::s_strResourcePath;
#endif // D2D_ANDROID_JNI

// debug
#include "common/Log.h"

FileSystem* FileSystem::Instance()
{
	if (!m_instance)
	{
		m_instance = new FileSystem;
	}
	return m_instance;
}

std::string FileSystem::getAbsolutePath(const std::string& filename) const
{
#ifdef D2D_WINDOWS
	return m_winRoot + filename;
#else
	return filename;
#endif
}

#ifdef D2D_ANDROID_JNI

void FileSystem::setResourcePath(const char* pszResourcePath)
{
	std::string tmp(pszResourcePath);

	if ((! pszResourcePath) || tmp.find(".apk") == std::string::npos)
	{
		return;
	}

	s_strResourcePath = pszResourcePath;
}

unsigned char* FileSystem::getFileData(const char* pszFileName, const char* pszMode, unsigned long * pSize)
{    
	unsigned char* pData = 0;
	std::string fullPath(pszFileName);

	if ((! pszFileName) || (! pszMode))
	{
		return 0;
	}

	if (pszFileName[0] != '/')
	{
		// read from apk
		fullPath.insert(0, "assets/");
		pData =  getFileDataFromZip(s_strResourcePath.c_str(), fullPath.c_str(), pSize);
	}
	else
	{
		do 
		{
			// read rrom other path than user set it
			FILE *fp = fopen(pszFileName, pszMode);
			if (!fp) break;

			unsigned long size;
			fseek(fp,0,SEEK_END);
			size = ftell(fp);
			fseek(fp,0,SEEK_SET);
			pData = new unsigned char[size];
			size = fread(pData,sizeof(unsigned char), size,fp);
			fclose(fp);

			if (pSize)
			{
				*pSize = size;
			}            
		} while (0);        
	}

	return pData;
}

unsigned char* FileSystem::getFileDataFromZip(const char* pszZipFilePath, const char* pszFileName, unsigned long * pSize)
{
	unsigned char * pBuffer = NULL;
	unzFile pFile = NULL;
	*pSize = 0;

	do 
	{
		if (!pszZipFilePath || !pszFileName) break;
		if (strlen(pszZipFilePath) == 0) break;

		pFile = unzOpen(pszZipFilePath);
		if (!pFile) break;

		int nRet = unzLocateFile(pFile, pszFileName, 1);
		if (UNZ_OK != nRet) break;

		char szFilePathA[260];
		unz_file_info FileInfo;
		nRet = unzGetCurrentFileInfo(pFile, &FileInfo, szFilePathA, sizeof(szFilePathA), NULL, 0, NULL, 0);
		if (UNZ_OK != nRet) break;

		nRet = unzOpenCurrentFile(pFile);
		if (UNZ_OK != nRet) break;

		pBuffer = new unsigned char[FileInfo.uncompressed_size];
		int nSize = 0;
		nSize = unzReadCurrentFile(pFile, pBuffer, FileInfo.uncompressed_size);

		*pSize = FileInfo.uncompressed_size;

		unzCloseCurrentFile(pFile);
	} while (0);

	if (pFile)
	{
		unzClose(pFile);
	}

	return pBuffer;
}

#endif // D2D_ANDROID_JNI