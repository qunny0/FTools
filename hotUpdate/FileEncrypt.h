//
//  encrypt.h
//  FileEncrypt
//
//  Created by 李伟光 on 13-9-2.
//
//

#ifndef __FileEncrypt__encrypt__
#define __FileEncrypt__encrypt__

#include <iostream>
#if (CC_TARGET_PLATFORM != CC_PLATFORM_WIN32)
#include <dirent.h>
#include <sys/stat.h>
#else
//#include <io.h>
#endif

using namespace std;
///Users/fengkaiming/Documents/FileEncrypt_image/FileEncrypt/Classes/FileEncrypt.cpp
class FileEncrypt
{
public:
	FileEncrypt(const char* outputpath);

    void FindAllFile(string folderPath);
    void encryptFileByName(string pFileName);
    bool saveFile2(string pFileName,FILE *file);
    unsigned char* getFileData(const char* pszFileName, const char* pszMode, unsigned long * pSize);

private:
	string _outputPath;
};

#endif /* defined(__FileEncrypt__encrypt__) */
