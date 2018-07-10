//#include "FileUtils.h"
//
//#ifdef D2D_ANDROID_JNI
//
//#include <Minizip/unzip.h>
//#include <assert.h>
//
//using namespace d2d;
//
//// record the resource path
//std::string FileUtils::s_strResourcePath = "";
//
//void FileUtils::setResourcePath(const char* pszResourcePath)
//{
//	assert(pszResourcePath != NULL, "[FileUtils setRelativePath] -- wrong relative path");
//
//	std::string tmp(pszResourcePath);
//
//	if ((! pszResourcePath) || tmp.find(".apk") == std::string::npos)
//	{
//		return;
//	}
//
//	s_strResourcePath = pszResourcePath;
//}
//
//unsigned char* FileUtils::getFileDataJNI(const char* pszFileName, const char* pszMode, 
//										 unsigned long* pSize)
//{
//	unsigned char * pData = 0;
//	std::string fullPath(pszFileName);
//
//	if ((! pszFileName) || (! pszMode))
//	{
//		return 0;
//	}
//
//	if (pszFileName[0] != '/')
//	{
//		// read from apk
//		fullPath.insert(0, "assets/");
//		pData = getFileDataFromZip(s_strResourcePath.c_str(), fullPath.c_str(), pSize);
//	}
//	else
//	{
//		do 
//		{
//			// read rrom other path than user set it
//			FILE* fp = fopen(pszFileName, pszMode);
//			if (!fp) break;
//
//			unsigned long size;
//			fseek(fp, 0, SEEK_END);
//			size = ftell(fp);
//			fseek(fp, 0, SEEK_SET);
//			pData = new unsigned char[size];
//			size = fread(pData, sizeof(unsigned char), size, fp);
//			fclose(fp);
//
//			if (pSize)
//			{
//				*pSize = size;
//			}            
//		} while (0);        
//	}
//
//// 	if (! pData && isPopupNotify())
//// 	{
//// 		std::string title = "Notification";
//// 		std::string msg = "Get data from file(";
//// 		msg.append(fullPath.c_str()).append(") failed!");
//// 		CCMessageBox(msg.c_str(), title.c_str());
//// 	}
//
//	return pData;
//}
//
//unsigned char* FileUtils::getFileDataFromZip(const char* pszZipFilePath, const char* pszFileName, 
//											 unsigned long * pSize)
//{
//	unsigned char * pBuffer = NULL;
//	unzFile pFile = NULL;
//	*pSize = 0;
//
//	do 
//	{
//		if (!pszZipFilePath || !pszFileName) break;
//		if (strlen(pszZipFilePath) == 0) break;
//
//		pFile = unzOpen(pszZipFilePath);
//		if (!pFile) break;
//
//		int nRet = unzLocateFile(pFile, pszFileName, 1);
//		if (UNZ_OK != nRet) break;
//
//		char szFilePathA[260];
//		unz_file_info FileInfo;
//		nRet = unzGetCurrentFileInfo(pFile, &FileInfo, szFilePathA, sizeof(szFilePathA), NULL, 0, NULL, 0);
//		if (UNZ_OK != nRet) break;
//
//		nRet = unzOpenCurrentFile(pFile);
//		if (UNZ_OK != nRet) break;
//
//		pBuffer = new unsigned char[FileInfo.uncompressed_size];
//		int nSize = 0;
//		nSize = unzReadCurrentFile(pFile, pBuffer, FileInfo.uncompressed_size);
//		assert(nSize == 0 || nSize == (int)FileInfo.uncompressed_size, "the file size is wrong");
//
//		*pSize = FileInfo.uncompressed_size;
//		unzCloseCurrentFile(pFile);
//	} while (0);
//
//	if (pFile)
//	{
//		unzClose(pFile);
//	}
//
//	return pBuffer;
//}
//
//#endif // D2D_ANDROID_JNI